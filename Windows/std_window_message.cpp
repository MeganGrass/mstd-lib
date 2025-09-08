/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#include "std_window.h"

#pragma comment(lib, "Shcore.lib")


LRESULT CALLBACK StandardWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	Standard_Window* Window = (Standard_Window*)dwRefData;

	if (!Window) { return DefSubclassProc(hWnd, uMsg, wParam, lParam); }

#if MSTD_DEVICE
	Window->Device()->UpdateJoysticks();
#endif

	switch (uMsg)
	{
	case WM_MOVE:
		break;
	case WM_ACTIVATE:
		Window->MsgActivate(wParam, lParam);
		break;
	case WM_SETFOCUS:
		Window->MsgSetFocus(wParam, lParam);
		break;
	case WM_KILLFOCUS:
		Window->MsgKillFocus(wParam, lParam);
		break;
	case WM_WINDOWPOSCHANGING:
		break;
	case WM_WINDOWPOSCHANGED:
		//Window->MsgPositionChanged(wParam, lParam);
	{
		WINDOWPOS* WindowPos = (WINDOWPOS*)lParam;

		if (Window->IsToolBar())
		{
			SendMessage(Window->GetToolBar(), TB_AUTOSIZE, 0, 0);
			SendMessage(Window->GetToolBar(), WM_SIZE, 0, 0);
		}

		if (Window->IsStatusBar())
		{
			SendMessage(Window->GetStatusBar(), WM_SIZE, 0, MAKELPARAM(WindowPos->cx, WindowPos->cy));
			std::vector<INT> Parts(Window->GetStatusBarParts());
			LONG Width = WindowPos->cx / Window->GetStatusBarParts();
			INT RightEdge = Width;
			for (auto& Part : Parts)
			{
				Part = RightEdge;
				RightEdge += Width;
			}
			SendMessage(Window->GetStatusBar(), SB_SETPARTS, Window->GetStatusBarParts(), (LPARAM)Parts.data());
		}
	}
		break;
	case WM_DISPLAYCHANGE:
		Window->MsgDisplayChange(wParam, lParam);
		break;
#if MSTD_DEVICE
	case WM_INPUT_DEVICE_CHANGE:
		Window->Device()->MsgInputDeviceChange(wParam, lParam);
		break;
	case WM_INPUT:
		if ((Window->HasFocus()) && (GET_RAWINPUT_CODE_WPARAM(wParam) == RIM_INPUT)) { Window->Device()->MsgInput(hWnd, wParam, lParam); }
		break;
	case WM_TIMER:
		if (wParam == 1)
		{
			KillTimer(hWnd, 1);
			Window->Device()->ResetMouseDeltaZ();
		}
		if (wParam == 2)
		{
			KillTimer(hWnd, 2);
			Window->Device()->ResetMouseDeltaX();
		}
		break;
	case WM_MOUSEWHEEL:
		Window->Device()->MsgMouseWheel(wParam);
		SetTimer(hWnd, 1, 10, NULL);
		break;
	case WM_MOUSEHWHEEL:
		Window->Device()->MsgMouseHWheel(wParam);
		SetTimer(hWnd, 2, 10, NULL);
		break;
#endif
	case WM_DROPFILES:
		Window->MsgDropFiles(wParam, lParam);
		break;
	case WM_DPICHANGED:
		Window->MsgDpiChanged(wParam, lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (Window->GetBrush()) { FillRect(hdc, &ps.rcPaint, Window->GetBrush()); }
		EndPaint(hWnd, &ps);
	}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void Standard_Window::MsgActivate(WPARAM wParam, LPARAM lParam)
{
	if ((wParam & WA_ACTIVE) || (wParam & WA_CLICKACTIVE))
	{
		b_IsActive = true;
		DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &m_BorderColor, sizeof(COLORREF));
		DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &m_CaptionColor, sizeof(COLORREF));
		DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &m_TextColor, sizeof(COLORREF));
	}
	else
	{
		b_IsActive = false;
		DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &m_BorderColorLostFocus, sizeof(COLORREF));
		DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &m_CaptionColorLostFocus, sizeof(COLORREF));
		DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &m_TextColorLostFocus, sizeof(COLORREF));
	}
#if MSTD_DEVICE
	m_Devices.get()->MsgActivate(hWnd, wParam);
#endif
}

void Standard_Window::MsgSetFocus(WPARAM wParam, LPARAM lParam)
{
	b_HasFocus = true;
}

void Standard_Window::MsgKillFocus(WPARAM wParam, LPARAM lParam)
{
	b_HasFocus = false;
}

void Standard_Window::MsgPositionChanged(WPARAM wParam, LPARAM lParam)
{
	WINDOWPOS* WindowPos = (WINDOWPOS*)lParam;

	// if ((WindowPos->flags & SWP_NOSIZE) && (WindowPos->flags & SWP_NOMOVE)) { return; }

	RECT Rect{ WindowPos->x, WindowPos->y, (WindowPos->cx - WindowPos->x), (WindowPos->cy - WindowPos->y) };

	if (!AdjustWindowRectExForDpi(&Rect, GetWindowLong(hWnd, GWL_STYLE), GetMenu(hWnd) ? TRUE : FALSE, GetWindowLong(hWnd, GWL_EXSTYLE), m_WindowDPI = GetDpiForWindow(hWnd))) { GetErrorMessage(); }

	SetWindowPos(hWnd, 0, Rect.left, Rect.top, Rect.right, Rect.bottom, WindowPos->flags);	// SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	if (GetScaleFactorForMonitor(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &m_ScaleFactor) != S_OK) { GetErrorMessage(); }

	/*if (h_ToolBar)
	{
		SendMessage(h_ToolBar, TB_AUTOSIZE, 0, 0);
		SendMessage(h_ToolBar, WM_SIZE, 0, 0);
	}

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
	}*/
}

void Standard_Window::MsgDisplayChange(WPARAM wParam, LPARAM lParam) const
{
	if (IsFullscreen())
	{
		WINDOWPOS WindowPos{};
		WindowPos.hwnd = hWnd;
		WindowPos.hwndInsertAfter = nullptr;
		WindowPos.x = 0;
		WindowPos.y = 0;
		WindowPos.cx = LOWORD(lParam);
		WindowPos.cy = HIWORD(lParam);
		WindowPos.flags = SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS;
		SendMessage(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&WindowPos);
	}
}

void Standard_Window::MsgDropFiles(WPARAM wParam, LPARAM lParam)
{
	HDROP hDrop = (HDROP)wParam;

	DragQueryPoint(hDrop, &m_DropPoint);

	UINT Count = DragQueryFileW(hDrop, 0xFFFFFFFF, 0, 0);

	s_DroppedFiles.clear();
	s_DroppedFiles.shrink_to_fit();

	for (UINT iFile = 0; iFile < Count; iFile++)
	{
		UINT StrLen = DragQueryFileW(hDrop, iFile, 0, 0);
		std::vector<wchar_t> String(StrLen + sizeof(wchar_t));
		DragQueryFileW(hDrop, iFile, String.data(), StrLen + sizeof(wchar_t));
		s_DroppedFiles.push_back(String.data());
		//Message(L"Dropped: %ws", s_DroppedFiles[iFile].c_str());
	}

	DragFinish(hDrop);
}

void Standard_Window::MsgDpiChanged(WPARAM wParam, LPARAM lParam)
{
	m_SysDPI = GetDpiForSystem();
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