/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*
*/


#include "std_system.h"


/*
	Windows System Functionality
*/
std::unique_ptr<StdWinSystem> WinSystem = std::make_unique<StdWinSystem>();


/*
	Initialize common controls
*/
void Standard_Windows_System::InitCommonControls(void)
{
	INITCOMMONCONTROLSEX CommonControls{};
	CommonControls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	CommonControls.dwICC =
		ICC_WIN95_CLASSES |
		ICC_DATE_CLASSES |
		ICC_USEREX_CLASSES |
		ICC_COOL_CLASSES |
		ICC_INTERNET_CLASSES |
		ICC_PAGESCROLLER_CLASS |
		ICC_NATIVEFNTCTL_CLASS |
		ICC_STANDARD_CLASSES |
		ICC_LINK_CLASS;
	if (!InitCommonControlsEx(&CommonControls)) { GetErrorMessage(); }
}