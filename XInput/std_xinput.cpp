/*
*
*	Megan Grass
*	August 15, 2025
*
*/


#include "std_xinput.h"

#pragma comment(lib, "xinput.lib")


bool Standard_XInput::QueryState(DWORD Index, bool b_CheckConnection) try
{
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		if (b_CheckConnection)
		{
			std::memset(&m_Capabilities, 0, sizeof(XINPUT_CAPABILITIES));
			if (XInputGetCapabilities(Index, XINPUT_FLAG_GAMEPAD, &m_Capabilities) != ERROR_SUCCESS)
			{
				return false;
			}

			if (m_Capabilities.Type != XINPUT_DEVTYPE_GAMEPAD)
			{
				return false;
			}

			std::memset(&m_BatteryInformation, 0, sizeof(XINPUT_BATTERY_INFORMATION));
			if (XInputGetBatteryInformation(Index, BATTERY_DEVTYPE_GAMEPAD, &m_BatteryInformation) != ERROR_SUCCESS)
			{
				return false;
			}
		}

		std::memset(&m_State, 0, sizeof(XINPUT_STATE));
		if (XInputGetState(Index, &m_State) == ERROR_SUCCESS)
		{
			if (m_State.Gamepad.wButtons != 0 || m_State.Gamepad.bLeftTrigger != 0 || m_State.Gamepad.bRightTrigger != 0 ||
				m_State.Gamepad.sThumbLX != 0 || m_State.Gamepad.sThumbLY != 0 || m_State.Gamepad.sThumbRX != 0 || m_State.Gamepad.sThumbRY != 0)
			{
				m_Gamepad = m_State.Gamepad;
				return true;
			}

			return false;
		}
	}

	return false;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_XInput::GetBatteryInformation(DWORD Index, BYTE DeviceType) try
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	std::memset(&m_BatteryInformation, 0, sizeof(XINPUT_BATTERY_INFORMATION));
	return XInputGetBatteryInformation(Index, DeviceType, &m_BatteryInformation) == ERROR_SUCCESS;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_XInput::GetCapabilities(DWORD Index) try
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	std::memset(&m_Capabilities, 0, sizeof(XINPUT_CAPABILITIES));
	return XInputGetCapabilities(Index, XINPUT_FLAG_GAMEPAD, &m_Capabilities) == ERROR_SUCCESS;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_XInput::GetKeystroke(DWORD Index) try
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	std::memset(&m_Keystroke, 0, sizeof(XINPUT_KEYSTROKE));
	return XInputGetKeystroke(Index, 0, &m_Keystroke) == ERROR_SUCCESS;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_XInput::SetVibration(DWORD Index) try
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	return XInputSetState(Index, &m_Vibration) == ERROR_SUCCESS;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_XInput::SetVibration(DWORD Index, WORD LeftMotorSpeed, WORD RightMotorSpeed) try
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	m_Vibration.wLeftMotorSpeed = LeftMotorSpeed;
	m_Vibration.wRightMotorSpeed = RightMotorSpeed;

	return XInputSetState(Index, &m_Vibration) == ERROR_SUCCESS;
}
catch (...) { Exception(std::current_exception()); return false; }