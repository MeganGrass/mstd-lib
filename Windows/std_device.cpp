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
*
*/


#include "std_device.h"

#pragma comment(lib, "Winmm.lib")


/*
	Mice, keyboards, HID, joysticks and displays
*/
std::unique_ptr<StdWinDevice> WinDevices = std::make_unique<StdWinDevice>();


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


/*
	Add device using handle from WM_INPUT_DEVICE_CHANGE
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
	Remove device using handle from WM_INPUT_DEVICE_CHANGE
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
	Get text report for display devices
*/
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

}


/*
	Handle input from WM_INPUT
*/
void Windows_Devices::InputJoyStick(void)
{
	// Joysticks
	for (auto& Joystick : Joysticks)
	{
		joyGetPosEx(Joystick->ID, &Joystick->Info);
	}
}


/*
	Handle input from WM_INPUT
*/
void Windows_Devices::Input(HWND hWnd, RAWINPUT* pInput)
{
	// Error
	//if ((!hWnd) || (!pInput)) { return; }

	// Mouse
	if (pInput->header.dwType == RIM_TYPEMOUSE)
	{
		for (auto& Mouse : Mice)
		{
			if (Mouse->Handle == pInput->header.hDevice)
			{
				std::memcpy(&Mouse->Input, &pInput->data.mouse, sizeof(RAWMOUSE));

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
				if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_1_DOWN) { Mouse->ButtonL = TRUE; }
				else if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_1_UP) { Mouse->ButtonL = FALSE; }

				if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_2_DOWN) { Mouse->ButtonR = TRUE; }
				else if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_2_UP) { Mouse->ButtonR = FALSE; }

				if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_3_DOWN) { Mouse->ButtonM = TRUE; }
				else if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_3_UP) { Mouse->ButtonM = FALSE; }

				if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) { Mouse->Button4 = TRUE; }
				else if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_4_UP) { Mouse->Button4 = FALSE; }

				if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) { Mouse->Button5 = TRUE; }
				else if (Mouse->Input.usButtonFlags & RI_MOUSE_BUTTON_5_UP) { Mouse->Button5 = FALSE; }


				// Hovering and relative to client position
				if ((GetCursorPos(&Mouse->RelPos)) && (ScreenToClient(hWnd, &Mouse->RelPos)) && (GetClientRect(hWnd, &Rect)))
				{
					Mouse->IsHovering = PtInRect(&Rect, Mouse->RelPos);
				}

				if (Mouse->IsHovering) { Mouse->HovPos = Mouse->RelPos; }
				else { Mouse->HovPos = { 0 }; }

				// Complete
				return;
			}
		}
	}

	// Keyboard
	if (pInput->header.dwType == RIM_TYPEKEYBOARD)
	{
		for (auto& Keyboard : Keyboards)
		{
			if (pInput->header.hDevice == Keyboard->Handle)
			{
				std::memcpy(&Keyboard->Input, &pInput->data.keyboard, sizeof(RAWKEYBOARD));

				if (Keyboard->Input.Flags & RI_KEY_BREAK) { Keyboard->State[Keyboard->Input.VKey] = FALSE; }
				else { Keyboard->State[Keyboard->Input.VKey] = TRUE; }

				if (Keyboard->Input.Flags & RI_KEY_E0) { Keyboard->E0[Keyboard->Input.VKey] = TRUE; }
				else { Keyboard->E0[Keyboard->Input.VKey] = FALSE; }

				if (Keyboard->Input.Flags & RI_KEY_E1) { Keyboard->E1[Keyboard->Input.VKey] = TRUE; }
				else { Keyboard->E1[Keyboard->Input.VKey] = FALSE; }

				return;
			}
		}
	}

}


/*
	Handle input from WM_MOUSEWHEEL
*/
void Windows_Devices::MouseWheel(WPARAM wParam)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaZ = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}


/*
	Handle input from WM_MOUSEHWHEEL
*/
void Windows_Devices::MouseHWheel(WPARAM wParam)
{
	for (auto& Mouse : Mice)
	{
		Mouse->DeltaX = static_cast<FLOAT>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
	}
}