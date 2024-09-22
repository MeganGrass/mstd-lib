/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*		Add support for WM_DISPLAYCHANGE and WM_SYSCOMMAND
*
*/


#include "std_window.h"

#include <shellscalingapi.h>

#pragma comment(lib, "Shcore.lib")


// WM_ACTIVATE
void Standard_Window::MsgActivate(WPARAM wParam, LPARAM lParam)
{
	if ((wParam & WA_ACTIVE) || (wParam & WA_CLICKACTIVE))
	{
		b_IsActive = true;
		for (auto& Mouse : WinDevices->Mice)
		{
			TrackMouseEvent(&Mouse->Event);
		}
		for (auto& Joystick : WinDevices->Joysticks)
		{
			joySetCapture(hWnd, Joystick->ID, 0, 0);
		}
	}
	else
	{
		b_IsActive = false;
		for (auto& Mouse : WinDevices->Mice)
		{
			Mouse->ClearInput();
		}
		for (auto& Joystick : WinDevices->Joysticks)
		{
			joyReleaseCapture(Joystick->ID);
		}
	}
}


// WM_SETFOCUS
void Standard_Window::MsgSetFocus(WPARAM wParam, LPARAM lParam)
{
	b_HasFocus = true;
}


// WM_KILLFOCUS
void Standard_Window::MsgKillFocus(WPARAM wParam, LPARAM lParam)
{
	b_HasFocus = false;
}


// WM_WINDOWPOSCHANGED
void Standard_Window::MsgPositionChanged(WPARAM wParam, LPARAM lParam)
{

	WINDOWPOS* WindowPos = (WINDOWPOS*)lParam;

	if ((WindowPos->flags & SWP_NOSIZE) && (WindowPos->flags & SWP_NOMOVE)) { return; }

	// Window DPI/Scaling
	GetScaleFactorForMonitor(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &m_ScaleFactor);
	m_WindowDPI = GetDpiForWindow(hWnd);

	// Parent Window
	SetWindowPos(hWnd, 0, WindowPos->x, WindowPos->y, WindowPos->cx, WindowPos->cy, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);	// WindowPos->flags);

	// Tool Bar
	if (h_ToolBar)
	{
		SendMessage(h_ToolBar, TB_AUTOSIZE, 0, 0);
		SendMessage(h_ToolBar, WM_SIZE, 0, 0);
	}

	// Status Bar
	if (h_StatusBar)
	{
		SendMessage(h_StatusBar, WM_SIZE, 0, MAKELPARAM(WindowPos->cx, WindowPos->cy));
		std::vector<INT> Parts(m_StatusBarParts);
		LONG Width = WindowPos->cx / m_StatusBarParts;
		INT RightEdge = Width;
		for (auto& Part : Parts)
		{
			Part = RightEdge;
			RightEdge += Width;
		}
		SendMessage(h_StatusBar, SB_SETPARTS, m_StatusBarParts, (LPARAM)Parts.data());
	}
}


// WM_INPUT_DEVICE_CHANGE
void Standard_Window::MsgInputDeviceChange(WPARAM wParam, LPARAM lParam)
{
	if(wParam == GIDC_ARRIVAL) { WinDevices->AddDevice((HANDLE)lParam); }
	else if (wParam & GIDC_REMOVAL) { WinDevices->RemoveDevice((HANDLE)lParam); }
}


// WM_INPUT
void Standard_Window::MsgInput(WPARAM wParam, LPARAM lParam)
{
	// no focus, no input processing
	if ((!b_HasFocus) || (GET_RAWINPUT_CODE_WPARAM(wParam) != RIM_INPUT)) { return; }

	// Joysticks
	WinDevices->InputJoyStick();

	// Header
	UINT Size = 0;
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 0, &Size, sizeof(RAWINPUTHEADER)) == -1) { GetErrorMessage(); }

	if (!Size) { return; }

	// Input
	std::vector<BYTE> Buffer(Size);
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, Buffer.data(), &Size, sizeof(RAWINPUTHEADER)) == -1) { GetErrorMessage(); }

	RAWINPUT* Input = (RAWINPUT*)Buffer.data();

	// No handler for HID...
	if (Input->header.dwType == RIM_TYPEHID) { return; }

	// Mice and Keyboards
	WinDevices->Input(hWnd, Input);
	//Status(0, "%d, %d  %d, %d", WinDevices->Mice[0]->RelPrev.x, WinDevices->Mice[0]->RelPrev.y, WinDevices->Mice[0]->RelPos.x, WinDevices->Mice[0]->RelPos.y);
	//Status(1, "%d, %d", WinDevices->Mice[0]->HovPos.x, WinDevices->Mice[0]->HovPos.y);
	//Status(2, "%d, %d, %d, %d, %d", WinDevices->Mice[0]->ButtonL, WinDevices->Mice[0]->ButtonM, WinDevices->Mice[0]->ButtonR, WinDevices->Mice[0]->Button4, WinDevices->Mice[0]->Button5);

}


// WM_MOUSEWHEEL
void Standard_Window::MsgMouseWheel(WPARAM wParam, LPARAM lParam)
{
	for (auto& Mouse : WinDevices->Mice)
	{
		Mouse->DeltaZ = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}


// WM_MOUSEHWHEEL
void Standard_Window::MsgMouseHWheel(WPARAM wParam, LPARAM lParam)
{
	for (auto& Mouse : WinDevices->Mice)
	{
		Mouse->DeltaX = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}


// WM_DROPFILES
void Standard_Window::MsgDropFiles(WPARAM wParam, LPARAM lParam)
{
	HDROP hDrop = (HDROP)wParam;
	DragQueryPoint(hDrop, &m_DropPoint);
	UINT Count = DragQueryFileW(hDrop, 0xFFFFFFFF, 0, 0);
	for (UINT iFile = 0; iFile < Count; iFile++)
	{
		UINT StrLen = DragQueryFileW(hDrop, iFile, 0, 0);
		std::vector<wchar_t> String(StrLen + sizeof(wchar_t));
		DragQueryFileW(hDrop, iFile, String.data(), StrLen + sizeof(wchar_t));
		//OnDropFiles(String.data());
		Message(FormatCStyle(L"Dropped: %ws", String.data()));
	}
	DragFinish(hDrop);
}


// WM_DPICHANGED
void Standard_Window::MsgDpiChanged(WPARAM wParam, LPARAM lParam)
{
	RECT* Rect = (RECT*)lParam;
	WINDOWPOS WindowPos{};
	WindowPos.hwnd = hWnd;
	WindowPos.hwndInsertAfter = nullptr;
	WindowPos.x = Rect->left;
	WindowPos.y = Rect->top;
	WindowPos.cx = (Rect->right - Rect->left);
	WindowPos.cy = (Rect->bottom - Rect->top);
	WindowPos.flags = SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS;
	SendMessage(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&WindowPos);
}