/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#include "std_device.h"


std::vector<Windows_Display*> _DisplayBuffer;


typedef struct WindowsDisplayDeviceEnum
{

	DWORD iDevNum { 0 };

	static BOOL CALLBACK MonitorEnum(HMONITOR hMonitor, HDC hDC, LPRECT lpRect, LPARAM dwData)
	{
		WindowsDisplayDeviceEnum* pThis = reinterpret_cast<WindowsDisplayDeviceEnum*>(dwData);

		// Display
		Windows_Display* Display = new Windows_Display;
		Display->Handle = hMonitor;
		Display->Rect = *lpRect;

		// Info
		MONITORINFOEXW Info{};
		Info.cbSize = sizeof(Info);
		GetMonitorInfoW(hMonitor, &Info);
		std::memcpy(&Display->Info, &Info, sizeof(MONITORINFOEXW));

		// Device
		DISPLAY_DEVICEW DisplayDevice{};
		DisplayDevice.cb = sizeof(DisplayDevice);
		EnumDisplayDevicesW(Info.szDevice, pThis->iDevNum, &DisplayDevice, 0);
		std::memcpy(&Display->Device, &DisplayDevice, sizeof(DISPLAY_DEVICEW));

		// Mode
		DEVMODEW Mode{};
		Mode.dmSize = sizeof(DEVMODEW);
		DWORD iModeNum = 0;
		while (EnumDisplaySettingsW(Info.szDevice, iModeNum, &Mode) != 0)
		{
			Display->Mode.push_back(Mode);
			iModeNum++;
		}

		// Add
		_DisplayBuffer.push_back(Display);

		// Continue
		pThis->iDevNum++;
		return TRUE;
	}

	explicit WindowsDisplayDeviceEnum(void)
	{
		EnumDisplayMonitors(0, 0, MonitorEnum, reinterpret_cast<LPARAM>(this));
	}

} WindowsDisplayDeviceEnum;


void Windows_Devices::InitDisplayDevices(void)
{
	WindowsDisplayDeviceEnum RunEnumProc;
	for (auto& Display : _DisplayBuffer)
	{
		Displays.push_back(std::move(Display));
	}
	_DisplayBuffer.clear();
	_DisplayBuffer.shrink_to_fit();
}