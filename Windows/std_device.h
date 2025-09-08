/*
*
*	Megan Grass
*	January 01, 2024
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
	BOOL IsHovering;					// Is Hovering Client Area?
	POINT HovPos;						// Hovering Position in Client Area
	POINT RelPos;						// Relative Position to Client Area
	POINT RelPrev;						// Relative Position to Previous Frame
	BOOL ButtonL;						// Left Button State
	BOOL ButtonLUp;						// Left Button Up State
	BOOL ButtonR;						// Right Button State
	BOOL ButtonRUp;						// Middle Button Up State
	BOOL ButtonM;						// Middle Button State
	BOOL ButtonMUp;						// Button Button Up State
	BOOL Button4;						// Button 4 State
	BOOL Button4Up;						// Button Button Up State
	BOOL Button5;						// Button 5 State
	BOOL Button5Up;						// Button Button Up State
	FLOAT DeltaZ;						// Vertical Scroll Wheel Delta
	FLOAT DeltaX;						// Horizontal Scroll Wheel Delta


	/*
		Construction
	*/
	explicit Windows_Mouse(void) :
		Handle{ nullptr },
		Info{},
		Input{},
		IsHovering(0),
		HovPos{},
		RelPos{},
		RelPrev{},
		ButtonL(0),
		ButtonLUp(0),
		ButtonR(0),
		ButtonRUp(0),
		ButtonM(0),
		ButtonMUp(0),
		Button4(0),
		Button4Up(0),
		Button5(0),
		Button5Up(0),
		DeltaZ(0.0f),
		DeltaX(0.0f)
	{
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
		IsHovering = 0;
		std::memset(&HovPos, 0, sizeof(POINT));
		std::memset(&RelPos, 0, sizeof(POINT));
		std::memset(&RelPrev, 0, sizeof(POINT));
		ButtonL = FALSE;
		ButtonLUp = FALSE;
		ButtonR = FALSE;
		ButtonRUp = FALSE;
		ButtonM = FALSE;
		ButtonMUp = FALSE;
		Button4 = FALSE;
		Button4Up = FALSE;
		Button5 = FALSE;
		Button5Up = FALSE;
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


	/*
		Get state of key
		- async update of key state
	*/
	[[nodiscard]] BOOL GetState(BYTE Key, BOOL* E0 = FALSE, BOOL* E1 = FALSE) const
	{
		if (E0) *E0 = this->E0[Key];
		if (E1) *E1 = this->E1[Key];
		return State[Key];
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
	HMONITOR Handle{ nullptr };			// Monitor Handle
	RECT Rect{};						// Device-Context Coordinates
	MONITORINFOEXW Info{};				// Monitor Information
	DISPLAY_DEVICEW Device{};			// Display Device
	std::vector<DEVMODEW> Mode;			// Display Modes
} Windows_Display;


/*
	Windows Devices
*/
class Windows_Devices final :
	private Standard_Windows_Common {
private:


	std::vector<Windows_Mouse*> Mice;
	std::vector<Windows_Keyboard*> Keyboards;
	std::vector<Windows_HID*> HID;
	std::vector<Windows_Joystick*> Joysticks;
	std::vector<Windows_Display*> Displays;


	/*
		Locked button and key states
	*/
	BOOL b_MouseLeft;
	BOOL b_MouseRight;
	BOOL b_MouseMiddle;
	BOOL b_MouseButton4;
	BOOL b_MouseButton5;

	BOOL b_LockedKeyboardState[256];

	UINT m_MouseDelayDeltaZ;
	UINT m_MouseDelayDeltaX;


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


	/*
		Construction
	*/
	explicit Windows_Devices(void) :
		Mice{},
		Keyboards{},
		HID{},
		Joysticks{},
		Displays{},
		b_MouseLeft{ FALSE },
		b_MouseRight{ FALSE },
		b_MouseMiddle{ FALSE },
		b_MouseButton4{ FALSE },
		b_MouseButton5{ FALSE },
		b_LockedKeyboardState{},
		m_MouseDelayDeltaZ{ 25 },
		m_MouseDelayDeltaX{ 25 }
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
		Mice.shrink_to_fit();
		Keyboards.clear();
		Keyboards.shrink_to_fit();
		HID.clear();
		HID.shrink_to_fit();
		Joysticks.clear();
		Joysticks.shrink_to_fit();
		Displays.clear();
		Displays.shrink_to_fit();
	}


	/*
		Get text report for display devices
	*/
#ifdef _DEBUG
	//void GetDisplayReport(void);
#endif


	/*
		Get mouse count
	*/
	[[nodiscard]] std::size_t GetMouseCount(void) const { return Mice.size(); }


	/*
		Get keyboard count
	*/
	[[nodiscard]] std::size_t GetKeyboardCount(void) const { return Keyboards.size(); }


	/*
		Get HID count
	*/
	[[nodiscard]] std::size_t GetHIDCount(void) const { return HID.size(); }


	/*
		Get joystick count
	*/
	[[nodiscard]] std::size_t GetJoystickCount(void) const { return Joysticks.size(); }


	/*
		Get display count
	*/
	[[nodiscard]] std::size_t GetDisplayCount(void) const { return Displays.size(); }


	/*
		Update joystick state
	*/
	void UpdateJoysticks(void);


	/*
		Intended for use with WM_INPUT_DEVICE_CHANGE
	*/
	void AddDevice(HANDLE hDevice);


	/*
		Intended for use with WM_INPUT_DEVICE_CHANGE
	*/
	void RemoveDevice(HANDLE hDevice);


	/*
		Intended for use with WM_ACTIVATE
	*/
	void MsgActivate(HWND hWnd, WPARAM wParam);


	/*
		Intended for use with WM_INPUT_DEVICE_CHANGE
	*/
	void MsgInputDeviceChange(WPARAM wParam, LPARAM lParam);


	/*
		Intended for use with WM_INPUT
	*/
	void MsgInput(HWND hWnd, WPARAM wParam, LPARAM lParam);


	/*
		Intended for use with WM_INPUT
	*/
	void MsgInputJoyStick(void);


	/*
		Intended for use with WM_MOUSEWHEEL
	*/
	void MsgMouseWheel(WPARAM wParam);


	/*
		Intended for use with WM_MOUSEHWHEEL
	*/
	void MsgMouseHWheel(WPARAM wParam);


	/*
		Is the mouse hovering over the client area?
	*/
	[[nodiscard]] BOOL IsHovering(void) const;


	/*
		Is the mouse hovering over a position in the client area?
	*/
	[[nodiscard]] BOOL IsHoveringPos(RECT Position) const;


	/*
		Get mouse hovering position in the client area
	*/
	[[nodiscard]] POINT GetHoveringPosition(void) const;


	/*
		Get mouse relative position to the client area
	*/
	[[nodiscard]] POINT GetRelativePosition(void) const;


	/*
		Get mouse relative position to the previous frame
	*/
	[[nodiscard]] POINT GetRelativeToPrevious(void) const;


	/*
		Get state of mouse left button
	*/
	[[nodiscard]] BOOL GetMouseLeft(void);


	/*
		Get state of mouse right button
	*/
	[[nodiscard]] BOOL GetMouseRight(void);


	/*
		Get state of mouse middle button
	*/
	[[nodiscard]] BOOL GetMouseMiddle(void);


	/*
		Get state of mouse button 4
	*/
	[[nodiscard]] BOOL GetMouseButton4(void);


	/*
		Get state of mouse button 5
	*/
	[[nodiscard]] BOOL GetMouseButton5(void);


	/*
		Get mouse vertical scroll wheel delay
		 - default is 25ms
	*/
	UINT MouseDelayDeltaZ(void) const { return m_MouseDelayDeltaZ; }


	/*
		Get mouse horizontal scroll wheel delay
		 - default is 25ms
	*/
	UINT MouseDelayDeltaX(void) const { return m_MouseDelayDeltaX; }


	/*
		Get mouse vertical scroll wheel delta
	*/
	[[nodiscard]] FLOAT GetMouseDeltaZ(void) const;


	/*
		Get mouse horizontal scroll wheel delta
	*/
	[[nodiscard]] FLOAT GetMouseDeltaX(void) const;


	/*
		Reset mouse horizontal scroll wheel delta
	*/
	void ResetMouseDeltaX(void);


	/*
		Reset mouse vertical scroll wheel delta
	*/
	void ResetMouseDeltaZ(void);


	/*
		Get keyboard key state
		- async update of key state
	*/
	[[nodiscard]] BOOL GetKeyState(BYTE Key, BOOL* E0 = nullptr, BOOL* E1 = nullptr);


	/*
		Get down state of keyboard key
		- single update of state
	*/
	[[nodiscard]] BOOL GetKeyDown(BYTE Key, BOOL* E0 = nullptr, BOOL* E1 = nullptr);

};