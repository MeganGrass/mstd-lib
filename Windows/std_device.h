/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
* 
*		GetDeviceCaps
*
*		Make Windows_Devices a singleton
* 
*		Binding functionality
*
*/


#pragma once

#include "std_common.h"


/*
	Windows Mouse
*/
class Windows_Mouse {
private:
public:

	StringW Name;						// Device Name
	HANDLE Handle;						// Device Handle
	RID_DEVICE_INFO_MOUSE Info;			// Device Information
	RAWMOUSE Input;						// Raw Input Data
	TRACKMOUSEEVENT Event;				// Tracking Event
	BOOL IsHovering;					// Is Hovering Client Area?
	POINT HovPos;						// Hovering Position in Client Area
	POINT RelPos;						// Relative Position to Client Area
	POINT RelPrev;						// Relative Position to Previous Frame
	BOOL ButtonL;						// Left Button State
	BOOL ButtonR;						// Right Button State
	BOOL ButtonM;						// Middle Button State
	BOOL Button4;						// Button 4 State
	BOOL Button5;						// Button 5 State
	FLOAT DeltaZ;						// Vertical Scroll Wheel Delta
	FLOAT DeltaX;						// Horizontal Scroll Wheel Delta


	/*
		Construction
	*/
	explicit Windows_Mouse(void) :
		Handle{ nullptr },
		Info{},
		Input{},
		Event{},
		IsHovering(0),
		HovPos{},
		RelPos{},
		RelPrev{},
		ButtonL(0),
		ButtonR(0),
		ButtonM(0),
		Button4(0),
		Button5(0),
		DeltaZ(0.0f),
		DeltaX(0.0f)
	{
		Event.cbSize = sizeof(TRACKMOUSEEVENT);
	}


	/*
		Deconstruction
	*/
	virtual ~Windows_Mouse(void)
	{
		Name.clear();
		Handle = nullptr;
		std::memset(&Info, 0, sizeof(RID_DEVICE_INFO_MOUSE));
		ClearInput();
	}

	void ClearInput(void)
	{
		std::memset(&Input, 0, sizeof(RAWMOUSE));
		std::memset(&Event, 0, sizeof(TRACKMOUSEEVENT));
		IsHovering = 0;
		std::memset(&HovPos, 0, sizeof(POINT));
		std::memset(&RelPos, 0, sizeof(POINT));
		std::memset(&RelPrev, 0, sizeof(POINT));
		ButtonL = 0;
		ButtonR = 0;
		ButtonM = 0;
		Button4 = 0;
		Button5 = 0;
		DeltaZ = 0.0f;
		DeltaX = 0.0f;
	}

};


/*
	Windows Keyboard
*/
class Windows_Keyboard {
private:

public:

	StringW Name;						// Device Name
	HANDLE Handle;						// Device Handle
	RID_DEVICE_INFO_KEYBOARD Info;		// Device Information
	RAWKEYBOARD Input;					// Raw Input Data
	BOOL State[256];					// Key Pressed States
	BOOL E0[256];						// E0 Scan Code States
	BOOL E1[256];						// E1 Scan Code States


	/*
		Construction
	*/
	explicit Windows_Keyboard(void) :
		Handle{ nullptr },
		Info{},
		Input{},
		State{ 0 },
		E0{ 0 },
		E1{ 0 }
	{
	}


	/*
		Deconstruction
	*/
	virtual ~Windows_Keyboard(void)
	{
		Name.clear();
		Handle = nullptr;
		std::memset(&Info, 0, sizeof(RID_DEVICE_INFO_KEYBOARD));
		std::memset(&Input, 0, sizeof(RAWKEYBOARD));
		std::memset(State, 0, 256 * sizeof(BOOL));
		std::memset(E0, 0, 256 * sizeof(BOOL));
		std::memset(E1, 0, 256 * sizeof(BOOL));
	}

};


/*
	Windows HID
*/
class Windows_HID {
private:

public:

	StringW Name;						// Device Name
	HANDLE Handle;						// Device Handle
	RID_DEVICE_INFO_HID Info;			// Device Information
	RAWHID Input;						// Raw Input Data


	/*
		Construction
	*/
	explicit Windows_HID(void) :
		Handle{ nullptr },
		Info{},
		Input{}
	{
	}


	/*
		Deconstruction
	*/
	virtual ~Windows_HID(void)
	{
		Name.clear();
		Handle = nullptr;
		std::memset(&Info, 0, sizeof(RID_DEVICE_INFO_HID));
		std::memset(&Input, 0, sizeof(RAWKEYBOARD));
	}

};


/*
	Windows Joystick
*/
class Windows_Joystick {
private:

public:

	JOYINFOEX Info;
	JOYCAPSW Caps;
	UINT ID;


	/*
		Construction
	*/
	explicit Windows_Joystick(void) :
		Info{},
		Caps{},
		ID(0)
	{
		Info.dwSize = sizeof(JOYINFOEX);
		Info.dwFlags = JOY_RETURNALL;
	}


	/*
		Deconstruction
	*/
	virtual ~Windows_Joystick(void)
	{
		std::memset(&Info, 0, sizeof(JOYINFO));
		std::memset(&Caps, 0, sizeof(JOYINFOEX));
		ID = 0;
	}

};


/*
	Windows Display
*/
typedef struct Windows_Display
{
	HMONITOR Handle { nullptr };		// Monitor Handle
	RECT Rect{};						// Device-Context Coordinates
	MONITORINFOEXW Info{};				// Monitor Information
	DISPLAY_DEVICEW Device{};			// Display Device
	std::vector<DEVMODEW> Mode;			// Display Modes
} Windows_Display;


/*
	Windows Devices
*/
typedef class Windows_Devices StdWinDevice;
extern std::unique_ptr<StdWinDevice> WinDevices;
class Windows_Devices final :
	private Standard_Windows_Common {
private:


	/*
		Initialize mice, keyboards, HID, joysticks and displays
	*/
	void Initialize(void);


	/*
		Initialize displays
	*/
	void InitDisplayDevices(void);


	/*
		Move
	*/
	Windows_Devices(Windows_Devices&&) = delete;
	Windows_Devices& operator = (Windows_Devices&&) = delete;


	/*
		Copy
	*/
	Windows_Devices(const Windows_Devices&) = delete;
	Windows_Devices& operator = (const Windows_Devices&) = delete;


public:


	std::vector<Windows_Mouse*> Mice;
	std::vector<Windows_Keyboard*> Keyboards;
	std::vector<Windows_HID*> HID;
	std::vector<Windows_Joystick*> Joysticks;
	std::vector<Windows_Display*> Displays;


	/*
		Construction
	*/
	explicit Windows_Devices(void)
	{
		Initialize();
	}


	/*
		Deconstruction
	*/
	virtual ~Windows_Devices(void)
	{
		for (auto& Joystick : Joysticks)
		{
			joyReleaseCapture(Joystick->ID);
		}
		Mice.clear();
		Keyboards.clear();
		HID.clear();
		Joysticks.clear();
		Displays.clear();
	}


	/*
		Add device using handle from WM_INPUT_DEVICE_CHANGE
	*/
	void AddDevice(HANDLE hDevice);


	/*
		Remove device using handle from WM_INPUT_DEVICE_CHANGE
	*/
	void RemoveDevice(HANDLE hDevice);


	/*
		Get text report for display devices
	*/
#ifdef _DEBUG
	//void GetDisplayReport(void);
#endif


	/*
		Handle input from WM_INPUT
	*/
	void InputJoyStick(void);


	/*
		Handle input from WM_INPUT
	*/
	void Input(HWND hWnd, RAWINPUT* pInput);


	/*
		Handle input from WM_MOUSEWHEEL
	*/
	void MouseWheel(WPARAM wParam);


	/*
		Handle input from WM_MOUSEHWHEEL
	*/
	void MouseHWheel(WPARAM wParam);


};