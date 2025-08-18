/*
*
*	Megan Grass
*	August 15, 2025
*
*/


#pragma once

#include "std_common.h"

#include <mutex>

#include <Xinput.h>


/*
	Standard X-Input
*/
class Standard_XInput final :
	protected Standard_Exception {
private:

	std::mutex m_Mutex;

	XINPUT_BATTERY_INFORMATION m_BatteryInformation;

	XINPUT_CAPABILITIES m_Capabilities;

	XINPUT_GAMEPAD m_Gamepad;

	XINPUT_KEYSTROKE m_Keystroke;

	XINPUT_STATE m_State;

	XINPUT_VIBRATION m_Vibration;

	bool QueryState(DWORD Index, bool b_CheckConnection);

public:

	explicit Standard_XInput(void) :
		m_BatteryInformation{},
		m_Capabilities{},
		m_Gamepad{},
		m_Keystroke{},
		m_State{},
		m_Vibration{}
	{
	}
	virtual ~Standard_XInput(void) = default;

	const XINPUT_BATTERY_INFORMATION& BatteryInformation(void) const { return m_BatteryInformation; }

	const XINPUT_CAPABILITIES& Capabilities(void) const { return m_Capabilities; }

	const XINPUT_GAMEPAD& Gamepad(void) const { return m_Gamepad; }

	const XINPUT_KEYSTROKE& Keystroke(void) const { return m_Keystroke; }

	const XINPUT_STATE& State(void) const { return m_State; }

	const XINPUT_VIBRATION& Vibration(void) const { return m_Vibration; }

	bool GetBatteryInformation(DWORD Index = 0, BYTE DeviceType = BATTERY_DEVTYPE_GAMEPAD);

	bool GetCapabilities(DWORD Index = 0);

	bool GetKeystroke(DWORD Index = 0);

	bool SetVibration(DWORD Index = 0);

	bool SetVibration(DWORD Index, WORD LeftMotorSpeed, WORD RightMotorSpeed);

	bool IsConnected(DWORD Index = 0) { return QueryState(Index, true); }

	bool PollState(DWORD Index = 0) { return QueryState(Index, false); }

};