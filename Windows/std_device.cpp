/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*
*		Add joystick support to AddDevice
*		Add joystick support to RemoveDevice
*		Maybe add support for RI_MOUSE_WHEEL and RI_MOUSE_HWHEEL
*		Add HIDClass support
*
*/


#include "std_device.h"

#pragma comment(lib, "Winmm.lib")


/*
	Initialize mice, keyboards, HID, joysticks and displays
*/
void Windows_Devices::Initialize(void)
{
	// Get Device Count
	UINT nDevices = 0;
	if (GetRawInputDeviceList(0, &nDevices, sizeof(RAWINPUTDEVICELIST)) == (UINT)-1) { GetErrorMessage(); }

	// Get Raw Input Device List
	std::vector<RAWINPUTDEVICELIST> InputDeviceList(nDevices);
	if (GetRawInputDeviceList(InputDeviceList.data(), &nDevices, sizeof(RAWINPUTDEVICELIST)) == (UINT)-1) { GetErrorMessage(); }

	// Parse and Register Raw Input Devices
	UINT ID = 0;
	while (nDevices--)
	{
		AddDevice(InputDeviceList[ID].hDevice);
		ID++;
	}

	// Joystick
	UINT nJoy = joyGetNumDevs();
	for (UINT ID = 0; ID < nJoy; ID++)
	{
		JOYINFOEX InfoEx{};
		InfoEx.dwSize = sizeof(JOYINFOEX);
		InfoEx.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(ID, &InfoEx) == JOYERR_NOERROR)
		{
			JOYCAPSW Caps{};
			if (joyGetDevCapsW(ID, &Caps, sizeof(JOYCAPSW)) == JOYERR_NOERROR)
			{
				Windows_Joystick* Joystick = new Windows_Joystick;

				std::memcpy(&Joystick->Info, &InfoEx, sizeof(JOYINFOEX));
				std::memcpy(&Joystick->Caps, &Caps, sizeof(JOYCAPSW));
				Joystick->ID = ID;

				Joysticks.push_back(Joystick);
			}
		}
	}

	// Monitors
	InitDisplayDevices();
}


#ifdef _DEBUG
/*
	Get text report for display devices
//
#include "../std_text.h"
void Windows_Devices::GetDisplayReport(void)
{
	// C:\Users\%USER%\Documents
	std::filesystem::path OriginalPath = GetUserDocumentsDir();

	// Parse
	int id = 0;
	for (auto& Display : Displays)
	{
		// Path
		std::filesystem::path Path = OriginalPath;
		Path /= L"DisplayReport" + std::to_wstring(id) + L".txt";

		// File
		StdText TextFile{ Path, FileAccessMode::Write_Ex, TextFileBOM::UTF8 };

		// Handle
		TextFile.AddLine("Handle: %p\r\n", Display->Handle);

		// Info
		TextFile.AddLine("Device: %ws\r\n", Display->Info.szDevice);
		TextFile.AddLine("Name: %ws\r\n", Display->Device.DeviceName);
		TextFile.AddLine("Description: %ws\r\n", Display->Device.DeviceString);

		// Rect
		TextFile.AddLine("rcDevice: %d, %d, %d, %d\r\n", Display->Rect.left, Display->Rect.top, Display->Rect.right, Display->Rect.bottom);
		TextFile.AddLine("rcMonitor: %d, %d, %d, %d\r\n", Display->Info.rcMonitor.left, Display->Info.rcMonitor.top, Display->Info.rcMonitor.right, Display->Info.rcMonitor.bottom);
		TextFile.AddLine("rcWork: %d, %d, %d, %d\r\n", Display->Info.rcWork.left, Display->Info.rcWork.top, Display->Info.rcWork.right, Display->Info.rcWork.bottom);

		// Flags
		if (Display->Info.dwFlags) { TextFile.AddLine("Flags: MONITORINFOF_PRIMARY\r\n"); }

		// State Flags
		String StateString = "State Flags: ";
		if (Display->Device.StateFlags == 0) { StateString += "0"; }
		else
		{
			if (Display->Device.StateFlags & DISPLAY_DEVICE_ACTIVE) { StateString += "DISPLAY_DEVICE_ACTIVE"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_ATTACHED) { StateString += " | DISPLAY_DEVICE_ATTACHED"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) { StateString += " | DISPLAY_DEVICE_MIRRORING_DRIVER"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_MODESPRUNED) { StateString += " | DISPLAY_DEVICE_MODESPRUNED"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) { StateString += " | DISPLAY_DEVICE_PRIMARY_DEVICE"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_REMOVABLE) { StateString += " | DISPLAY_DEVICE_REMOVABLE"; }
			if (Display->Device.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE) { StateString += " | DISPLAY_DEVICE_VGA_COMPATIBLE"; }
		}
		TextFile.AddLine(StateString + "\r\n");

		// Driver Name
		if (!Display->Mode.empty()) { TextFile.AddLine("Driver Name: %ws.dll\r\n", Display->Mode[0].dmDeviceName); }

		// Mode
		int iMode = 0;
		for (auto& Mode : Display->Mode)
		{
			TextFile.AddLine("\r\nMode: %d\r\n", iMode);

			// Fields
			//TextFile.AddLine("Fields: %X\r\n", Mode.dmFields);
			if (Mode.dmFields & DM_PELSWIDTH) { TextFile.AddLine("Pixel Width: %d\r\n", Mode.dmPelsWidth); }
			if (Mode.dmFields & DM_PELSHEIGHT) { TextFile.AddLine("Pixel Height: %d\r\n", Mode.dmPelsHeight); }
			if (Mode.dmFields & DM_BITSPERPEL) { TextFile.AddLine("Bits Per Pixel: %d\r\n", Mode.dmBitsPerPel); }
			if (Mode.dmFields & DM_DISPLAYFREQUENCY) { TextFile.AddLine("Display Frequency: %d\r\n", Mode.dmDisplayFrequency); }
			if (Mode.dmFields & DM_ORIENTATION) { TextFile.AddLine("Orientation: %d\r\n", Mode.dmOrientation); }
			if (Mode.dmFields & DM_PAPERSIZE) { TextFile.AddLine("Paper Size: %d\r\n", Mode.dmPaperSize); }
			if (Mode.dmFields & DM_PAPERLENGTH) { TextFile.AddLine("Paper Length: %d\r\n", Mode.dmPaperLength); }
			if (Mode.dmFields & DM_PAPERWIDTH) { TextFile.AddLine("Paper Width: %d\r\n", Mode.dmPaperWidth); }
			if (Mode.dmFields & DM_SCALE) { TextFile.AddLine("Scale: %d\r\n", Mode.dmScale); }
			if (Mode.dmFields & DM_POSITION) { TextFile.AddLine("Position: %d, %d\r\n", Mode.dmPosition.x, Mode.dmPosition.y); }
			if (Mode.dmFields & DM_NUP) { TextFile.AddLine("Nup: %d\r\n", Mode.dmNup); }
			if (Mode.dmFields & DM_DISPLAYORIENTATION)
			{
				String OrientationString = "Display Orientation: ";
				if (Mode.dmDisplayFlags == DMDO_DEFAULT) { OrientationString += "DMDO_DEFAULT"; }
				if (Mode.dmDisplayFlags & DMDO_90) { OrientationString += "DMDO_90"; }
				if (Mode.dmDisplayFlags & DMDO_180) { OrientationString += "DMDO_180"; }
				if (Mode.dmDisplayFlags & DMDO_270) { OrientationString += "DMDO_270"; }
				TextFile.AddLine(OrientationString + "\r\n");
			}
			if (Mode.dmFields & DM_COPIES) { TextFile.AddLine("Copies: %d\r\n", Mode.dmCopies); }
			if (Mode.dmFields & DM_DEFAULTSOURCE) { TextFile.AddLine("Default Source: %d\r\n", Mode.dmDefaultSource); }
			if (Mode.dmFields & DM_PRINTQUALITY) { TextFile.AddLine("Print Quality: %d\r\n", Mode.dmPrintQuality); }
			if (Mode.dmFields & DM_COLOR) { TextFile.AddLine("Color: %d\r\n", Mode.dmColor); }
			if (Mode.dmFields & DM_DUPLEX) { TextFile.AddLine("Duplex: %d\r\n", Mode.dmDuplex); }
			if (Mode.dmFields & DM_YRESOLUTION) { TextFile.AddLine("Y Resolution: %d\r\n", Mode.dmYResolution); }
			if (Mode.dmFields & DM_TTOPTION) { TextFile.AddLine("TT Option: %d\r\n", Mode.dmTTOption); }
			if (Mode.dmFields & DM_COLLATE) { TextFile.AddLine("Collate: %d\r\n", Mode.dmCollate); }
			if (Mode.dmFields & DM_FORMNAME) { TextFile.AddLine("Form Name: %ws\r\n", Mode.dmFormName); }
			if (Mode.dmFields & DM_LOGPIXELS) { TextFile.AddLine("Logical Pixels: %d\r\n", Mode.dmLogPixels); }
			if (Mode.dmFields & DM_ICMMETHOD) { TextFile.AddLine("ICM Method: %d\r\n", Mode.dmICMMethod); }
			if (Mode.dmFields & DM_ICMINTENT) { TextFile.AddLine("ICM Intent: %d\r\n", Mode.dmICMIntent); }
			if (Mode.dmFields & DM_MEDIATYPE) { TextFile.AddLine("Media Type: %d\r\n", Mode.dmMediaType); }
			if (Mode.dmFields & DM_DITHERTYPE) { TextFile.AddLine("Dither Type: %d\r\n", Mode.dmDitherType); }
			if (Mode.dmFields & DM_PANNINGWIDTH) { TextFile.AddLine("Panning Width: %d\r\n", Mode.dmPanningWidth); }
			if (Mode.dmFields & DM_PANNINGHEIGHT) { TextFile.AddLine("Panning Height: %d\r\n", Mode.dmPanningHeight); }
			if (Mode.dmFields & DM_DISPLAYFIXEDOUTPUT)
			{
				String FixedOutputString = "Display Fixed Output: ";
				if (Mode.dmDisplayFixedOutput == DMDFO_DEFAULT) { FixedOutputString += "DMDFO_DEFAULT"; }
				if (Mode.dmDisplayFixedOutput & DMDFO_CENTER) { FixedOutputString += "DMDFO_CENTER"; }
				if (Mode.dmDisplayFixedOutput & DMDFO_STRETCH) { FixedOutputString += "DMDFO_STRETCH"; }
				TextFile.AddLine(FixedOutputString + "\r\n");
			}
			if (Mode.dmFields & DM_DISPLAYFLAGS)
			{
				if (Mode.dmDisplayFlags)
				{
					String DisplayString = "Display Flags: ";
					if (Mode.dmDisplayFlags == 1) { DisplayString += "DM_GRAYSCALE"; }
					if (Mode.dmDisplayFlags & DM_INTERLACED) { DisplayString += "DM_INTERLACED"; }
					if (Mode.dmDisplayFlags & DMDISPLAYFLAGS_TEXTMODE) { DisplayString += "DMDISPLAYFLAGS_TEXTMODE"; }
					TextFile.AddLine(DisplayString + "\r\n");
				}
			}

			// Complete
			iMode++;
		}

		// Complete
		id++;
		TextFile.FlushUTF8();
	}

	// Complete
	StringW ReportStr;
	for (std::size_t n = 0; n < Displays.size(); n++) { ReportStr += FormatCStyle(L"DisplayReport%d.txt\r\n", n); }
	Message(L"Display Report files created in %ws\r\n\r\n%ws", OriginalPath.wstring().c_str(), ReportStr.c_str());

}*/
#endif


/*
	Update joystick state
*/
void Windows_Devices::UpdateJoysticks(void)
{
	for (auto& Joystick : Joysticks)
	{
		joyGetPosEx(Joystick->ID, &Joystick->Info);
	}
}


/*
	Intended for use with WM_INPUT_DEVICE_CHANGE
*/
void Windows_Devices::AddDevice(HANDLE hDevice)
{
	// Input Device
	RAWINPUTDEVICE InputDevice{};

	// Name
	UINT Size = _MAX_PATH * 2;
	wchar_t DeviceName[_MAX_PATH * 2]{};
	GetRawInputDeviceInfoW(hDevice, RIDI_DEVICENAME, &DeviceName, &Size);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }

	// Info
	Size = sizeof(RID_DEVICE_INFO);
	RID_DEVICE_INFO Info{};
	Info.cbSize = sizeof(RID_DEVICE_INFO);
	GetRawInputDeviceInfoW(hDevice, RIDI_DEVICEINFO, &Info, &Size);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }

	// Type
	switch (Info.dwType)
	{
	case RIM_TYPEMOUSE:
	{
		Windows_Mouse* _Mouse = new Windows_Mouse;
		_Mouse->Name = DeviceName;
		_Mouse->Handle = hDevice;
		std::memcpy(&_Mouse->Info, &Info.mouse, sizeof(RID_DEVICE_INFO_MOUSE));
		Mice.push_back(_Mouse);
	}
	InputDevice.usUsagePage = 0x01;
	InputDevice.usUsage = 0x02;
	InputDevice.dwFlags = 0;
	InputDevice.hwndTarget = 0;
	break;
	case RIM_TYPEKEYBOARD:
	{
		Windows_Keyboard* _Keyboard = new Windows_Keyboard;
		_Keyboard->Name = DeviceName;
		_Keyboard->Handle = hDevice;
		std::memcpy(&_Keyboard->Info, &Info.keyboard, sizeof(RID_DEVICE_INFO_KEYBOARD));
		Keyboards.push_back(_Keyboard);
	}
	InputDevice.usUsagePage = 0x01;
	InputDevice.usUsage = 0x06;
	InputDevice.dwFlags = 0;
	InputDevice.hwndTarget = 0;
	break;
	case RIM_TYPEHID:
	{
		Windows_HID* _HID = new Windows_HID;
		_HID->Name = DeviceName;
		_HID->Handle = hDevice;
		std::memcpy(&_HID->Info, &Info.hid, sizeof(RID_DEVICE_INFO_HID));
		HID.push_back(_HID);
	}
	InputDevice.usUsagePage = Info.hid.usUsagePage;
	InputDevice.usUsage = Info.hid.usUsage;
	InputDevice.dwFlags = 0;
	InputDevice.hwndTarget = 0;
	break;
	}

	// Register
	if (!RegisterRawInputDevices(&InputDevice, 1, sizeof(RAWINPUTDEVICE))) { GetErrorMessage(); }
}


/*
	Intended for use with WM_INPUT_DEVICE_CHANGE
*/
void Windows_Devices::RemoveDevice(HANDLE hDevice)
{
	// Mouse
	for (auto& Mouse : Mice)
	{
		if (Mouse->Handle == hDevice)
		{
			Mice.erase(std::remove(Mice.begin(), Mice.end(), Mouse), Mice.end());
			return;
		}
	}

	// Keyboard
	for (auto& Keyboard : Keyboards)
	{
		if (Keyboard->Handle == hDevice)
		{
			Keyboards.erase(std::remove(Keyboards.begin(), Keyboards.end(), Keyboard), Keyboards.end());
			return;
		}
	}

	// HID
	for (auto& _HID : HID)
	{
		if (_HID->Handle == hDevice)
		{
			HID.erase(std::remove(HID.begin(), HID.end(), _HID), HID.end());
			return;
		}
	}
}


/*
	Intended for use with WM_ACTIVATE
*/
void Windows_Devices::MsgActivate(HWND hWnd, WPARAM wParam)
{
	if ((wParam & WA_ACTIVE) || (wParam & WA_CLICKACTIVE))
	{
		TRACKMOUSEEVENT Event{};
		Event.cbSize = sizeof(TRACKMOUSEEVENT);
		Event.dwFlags = TME_LEAVE;
		Event.hwndTrack = hWnd;
		TrackMouseEvent(&Event);
		for (auto& Joystick : Joysticks)
		{
			joySetCapture(hWnd, Joystick->ID, 0, 0);
		}
	}
	else
	{
		for (auto& Mouse : Mice)
		{
			Mouse->ClearInput();
		}
		for (auto& Joystick : Joysticks)
		{
			joyReleaseCapture(Joystick->ID);
		}
	}
}


/*
	Intended for use with WM_INPUT_DEVICE_CHANGE
*/
void Windows_Devices::MsgInputDeviceChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == GIDC_ARRIVAL) { AddDevice((HANDLE)lParam); }
	else if (wParam & GIDC_REMOVAL) { RemoveDevice((HANDLE)lParam); }
}


/*
	Intended for use with WM_INPUT
*/
void Windows_Devices::MsgInput(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	UINT Size = 0;
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 0, &Size, sizeof(RAWINPUTHEADER)) == -1) { GetErrorMessage(); }
	if (!Size) { return; }

	std::vector<BYTE> Buffer(Size);
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, Buffer.data(), &Size, sizeof(RAWINPUTHEADER)) == -1) { GetErrorMessage(); }

	RAWINPUT* Input = (RAWINPUT*)Buffer.data();

	// No handler for HID...
	if (Input->header.dwType == RIM_TYPEHID) { return; }

	// Mouse
	if (Input->header.dwType == RIM_TYPEMOUSE)
	{
		for (auto& Mouse : Mice)
		{
			if (Mouse->Handle == Input->header.hDevice)
			{
				std::memcpy(&Mouse->Input, &Input->data.mouse, sizeof(RAWMOUSE));

				// Buffer
				RECT Rect{};

				// Relative to last position
				if (Mouse->Input.usFlags & MOUSE_MOVE_ABSOLUTE)
				{
					if (Mouse->Input.usFlags & MOUSE_VIRTUAL_DESKTOP)
					{
						Rect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
						Rect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
						Rect.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
						Rect.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
					}
					else
					{
						Rect.right = GetSystemMetrics(SM_CXSCREEN);
						Rect.bottom = GetSystemMetrics(SM_CYSCREEN);
					}
					Mouse->RelPrev.x = MulDiv(Mouse->Input.lLastX, Rect.right, 65535) + Rect.left;
					Mouse->RelPrev.y = MulDiv(Mouse->Input.lLastY, Rect.bottom, 65535) + Rect.top;
				}
				else if ((Mouse->Input.lLastX) || (Mouse->Input.lLastY))
				{
					Mouse->RelPrev.x = Mouse->Input.lLastX;
					Mouse->RelPrev.y = Mouse->Input.lLastY;
				}

				// Buttons
				Mouse->ButtonL = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_1_DOWN ? TRUE : FALSE;
				Mouse->ButtonLUp = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_1_UP ? TRUE : FALSE;
				Mouse->ButtonR = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_2_DOWN ? TRUE : FALSE;
				Mouse->ButtonRUp = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_2_UP ? TRUE : FALSE;
				Mouse->ButtonM = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_3_DOWN ? TRUE : FALSE;
				Mouse->ButtonMUp = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_3_UP ? TRUE : FALSE;
				Mouse->Button4 = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN ? TRUE : FALSE;
				Mouse->Button4Up = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_4_UP ? TRUE : FALSE;
				Mouse->Button5 = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN ? TRUE : FALSE;
				Mouse->Button5Up = Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_5_UP ? TRUE : FALSE;

				if (Mouse->ButtonLUp && b_MouseLeft) { b_MouseLeft = FALSE; }
				if (Mouse->ButtonRUp && b_MouseRight) { b_MouseRight = FALSE; }
				if (Mouse->ButtonMUp && b_MouseMiddle) { b_MouseMiddle = FALSE; }
				if (Mouse->Button4Up && b_MouseButton4) { b_MouseButton4 = FALSE; }
				if (Mouse->Button5Up && b_MouseButton5) { b_MouseButton5 = FALSE; }


				// Hovering and relative to client position
				if ((GetCursorPos(&Mouse->RelPos)) && (ScreenToClient(hWnd, &Mouse->RelPos)) && (GetClientRect(hWnd, &Rect)))
				{
					Mouse->IsHovering = PtInRect(&Rect, Mouse->RelPos);
				}

				Mouse->IsHovering ? Mouse->HovPos = Mouse->RelPos : Mouse->HovPos = { 0 };

				// Complete
				return;
			}
		}
	}

	// Keyboard
	if (Input->header.dwType == RIM_TYPEKEYBOARD)
	{
		for (auto& Keyboard : Keyboards)
		{
			if (Input->header.hDevice == Keyboard->Handle)
			{
				std::memcpy(&Keyboard->Input, &Input->data.keyboard, sizeof(RAWKEYBOARD));

				Keyboard->State[Keyboard->Input.VKey] = Keyboard->Input.Flags & RI_KEY_BREAK ? FALSE : TRUE;

				Keyboard->E0[Keyboard->Input.VKey] = Keyboard->Input.Flags & RI_KEY_E0 ? TRUE : FALSE;

				Keyboard->E1[Keyboard->Input.VKey] = Keyboard->Input.Flags & RI_KEY_E1 ? TRUE : FALSE;

				return;
			}
		}
	}

}


/*
	Intended for use with WM_INPUT
*/
void Windows_Devices::MsgInputJoyStick(void)
{
	// Joysticks
	for (auto& Joystick : Joysticks)
	{
		joyGetPosEx(Joystick->ID, &Joystick->Info);
	}
}


/*
	Intended for use with WM_MOUSEWHEEL
*/
void Windows_Devices::MsgMouseWheel(WPARAM wParam)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaZ = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}


/*
	Intended for use with WM_MOUSEHWHEEL
*/
void Windows_Devices::MsgMouseHWheel(WPARAM wParam)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaX = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}


/*
	Is the mouse hovering over the client area?
*/
BOOL Windows_Devices::IsHovering(void) const
{
	for (auto& Mouse : Mice)
	{
		if (Mouse->IsHovering) { return TRUE; }
	}
	return FALSE;
}


/*
	Is the mouse hovering over a position in the client area?
*/
BOOL Windows_Devices::IsHoveringPos(RECT Position) const
{
	for (auto& Mouse : Mice)
	{
		if ((Mouse->HovPos.x == 0) && (Mouse->HovPos.y == 0)) { continue; }
		if (PtInRect(&Position, Mouse->HovPos)) { return TRUE; }
	}
	return FALSE;
}


/*
	Get hovering position in the client area
*/
POINT Windows_Devices::GetHoveringPosition(void) const
{
	for (auto& Mouse : Mice)
	{
		if (Mouse->IsHovering) { return Mouse->HovPos; }
	}
	return { 0 };
}


/*
	Get mouse relative position to the client area
*/
POINT Windows_Devices::GetRelativePosition(void) const
{
	for (auto& Mouse : Mice)
	{
		if ((Mouse->RelPos.x == 0) && (Mouse->RelPos.y == 0)) { continue; }
		return Mouse->RelPos;
	}
	return { 0 };
}


/*
	Get mouse relative position to the previous frame
*/
POINT Windows_Devices::GetRelativeToPrevious(void) const
{
	for (auto& Mouse : Mice)
	{
		if ((Mouse->RelPrev.x == 0) && (Mouse->RelPrev.y == 0)) { continue; }
		return Mouse->RelPrev;
	}
	return { 0 };
}


/*
	Get state of mouse left button
*/
BOOL Windows_Devices::GetMouseLeft(void)
{
	if (b_MouseLeft) { return TRUE; }
	for (auto& Mouse : Mice)
	{
		if (Mouse->ButtonL) { return b_MouseLeft = TRUE; }
	}
	return b_MouseLeft = FALSE;
}


/*
	Get state of mouse right button
*/
BOOL Windows_Devices::GetMouseRight(void)
{
	if (b_MouseRight) { return TRUE; }
	for (auto& Mouse : Mice)
	{
		if (Mouse->ButtonR) { return b_MouseRight = TRUE; }
	}
	return b_MouseRight = FALSE;
}


/*
	Get state of mouse right button
*/
BOOL Windows_Devices::GetMouseMiddle(void)
{
	if (b_MouseMiddle) { return TRUE; }
	for (auto& Mouse : Mice)
	{
		if (Mouse->ButtonM) { return b_MouseMiddle = TRUE; }
	}
	return b_MouseMiddle = FALSE;
}


/*
	Get state of mouse button 4
*/
BOOL Windows_Devices::GetMouseButton4(void)
{
	if (b_MouseButton4) { return TRUE; }
	for (auto& Mouse : Mice)
	{
		if (Mouse->Button4) { return b_MouseButton4 = TRUE; }
	}
	return b_MouseButton4 = FALSE;
}


/*
	Get state of mouse button 5
*/
BOOL Windows_Devices::GetMouseButton5(void)
{
	if (b_MouseButton5) { return TRUE; }
	for (auto& Mouse : Mice)
	{
		if (Mouse->Button5) { return b_MouseButton5 = TRUE; }
	}
	return b_MouseButton5 = FALSE;
}


/*
	Get mouse vertical scroll wheel delta
*/
FLOAT Windows_Devices::GetMouseDeltaZ(void) const
{
	for (auto& Mouse : Mice)
	{
		if (Mouse->DeltaZ == 0.0f) { continue; }
		return Mouse->DeltaZ;
	}
	return 0.0f;
}


/*
	Get mouse horizontal scroll wheel delta
*/
FLOAT Windows_Devices::GetMouseDeltaX(void) const
{
	for (auto& Mouse : Mice)
	{
		if (Mouse->DeltaX == 0.0f) { continue; }
		return Mouse->DeltaX;
	}
	return 0.0f;
}


/*
	Reset mouse horizontal scroll wheel delta
*/
void Windows_Devices::ResetMouseDeltaX(void)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaX = 0.0f;
	}
}



/*
	Reset mouse vertical scroll wheel delta
*/
void Windows_Devices::ResetMouseDeltaZ(void)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaZ = 0.0f;
	}
}


/*
	Get keyboard state
*/
BOOL Windows_Devices::GetKeyState(BYTE Key, BOOL* E0, BOOL* E1)
{
	for (auto& Keyboard : Keyboards)
	{
		if (Keyboard->GetState(Key, E0, E1))
		{
			return TRUE;
		}
	}
	if (E0) *E0 = FALSE;
	if (E1) *E1 = FALSE;
	return FALSE;
}


/*
	Get down state of keyboard key
*/
BOOL Windows_Devices::GetKeyDown(BYTE Key, BOOL* E0, BOOL* E1)
{
	BOOL State = GetKeyState(Key, E0, E1);

	if (State && b_LockedKeyboardState[Key]) { return FALSE; }

	State ? b_LockedKeyboardState[Key] = TRUE : b_LockedKeyboardState[Key] = FALSE;

	return State;
}