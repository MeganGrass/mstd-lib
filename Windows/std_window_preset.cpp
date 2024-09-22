/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*
*/


#include "std_window.h"


// Preset command line parameters
void Standard_Window::PresetCommandLine(LPWSTR lpCmdLine)
{
	if (b_CreationComplete) { return; }
	StrVecW _Commandline = GetStrVec(lpCmdLine);
	for (auto& _Arg : _Commandline)
	{
		ToLower(_Arg);
		if (_Arg == L"-borderless") { b_Borderless = true; }
		if (_Arg == L"-fullscreen") { b_Fullscreen = true; }
	}
}

// Preset no window borders, frames or title/caption bar
void Standard_Window::PresetBorderless(bool Borderless)
{
	if (b_CreationComplete) { return; }
	b_Borderless = Borderless;
}

// Preset fullscreen window
void Standard_Window::PresetFullscreen(bool Fullscreen)
{
	if (b_CreationComplete) { return; }
	b_Fullscreen = Fullscreen;
}

// Preset Window Style
void Standard_Window::PresetStyle(DWORD Style)
{
	if (b_CreationComplete) { return; }
	m_Style = Style;
}

// Preset Window Extended Style
void Standard_Window::PresetStyleEx(DWORD StyleEx)
{
	if (b_CreationComplete) { return; }
	m_StyleEx = StyleEx;
}

// Preset Class Style
void Standard_Window::PresetClassStyle(UINT ClassStyle)
{
	if (b_CreationComplete) { return; }
	m_ClassStyle = ClassStyle;
}

// Preset class name
void Standard_Window::PresetClassName(const StringW ClassName)
{
	if (b_CreationComplete) { return; }
	s_ClassName = ClassName;
}

// Preset window name
void Standard_Window::PresetWindowName(const StringW Name)
{
	if (b_CreationComplete) { return; }
	s_Name = Name;
}

// Preset class name from resource string table (wide string)
void Standard_Window::PresetClassName(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	WCHAR ClassName[_MAX_PATH]{ 0 };
	if (LoadStringW(hInstance, ResourceID, ClassName, sizeof(ClassName) / sizeof(WCHAR)))
	{
		s_ClassName = ClassName;
	}
}

// Preset window name from resource string table (wide string)
void Standard_Window::PresetWindowName(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	WCHAR WindowName[_MAX_PATH]{ 0 };
	if (LoadStringW(hInstance, ResourceID, WindowName, sizeof(WindowName) / sizeof(WCHAR)))
	{
		s_Name = WindowName;
	}
}

// Preset window client rect color
void Standard_Window::PresetWindowColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush)
{
	if (b_CreationComplete) { return; }
	m_Color = RGB(Red, Green, Blue);
	h_Brush = CreateSolidBrush(m_Color);
	if (SetAsClassBrush) { b_ClassBrush = SetAsClassBrush; }
}

// Preset Window Icon
void Standard_Window::PresetIcon(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	h_Icon = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_Icon) { Message(L"An error occurred when trying to load the window icon."); }
}

// Preset Window Small Icon
void Standard_Window::PresetIconSm(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	h_IconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_IconSm) { Message(L"An error occurred when trying to load the window small icon."); }
}

// Preset HMENU
void Standard_Window::PresetMenu(HINSTANCE hInstance, WORD ResourceID)
{
	if (b_CreationComplete) { return; }
	h_Menu = LoadMenu(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_Menu) { b_Menu = false; Message(L"An error occurred when trying to load the window menu."); }
	else { b_Menu = true; m_MenuID = ResourceID; }
}

// Preset Tool Bar
void Standard_Window::PresetToolBar(UINT nButtons, UINT IconWidth, UINT IconHeight)
{
	if (b_CreationComplete) { return; }
	m_ToolBarButtonCount = nButtons;
	m_ToolBarIconWidth = IconWidth;
	m_ToolBarIconHeight = IconHeight;
	h_ToolBarImageList = ImageList_Create(m_ToolBarIconWidth, m_ToolBarIconHeight, ILC_COLOR32 | ILC_MASK, m_ToolBarButtonCount, 0);
}

// Preset Tool Bar Icon
// Create an Image List with PresetToolBar() before calling this function
void Standard_Window::PresetAddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	if (h_ToolBarImageList)
	{
		HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ResourceID), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
		if (hIcon)
		{
			ImageList_AddIcon(h_ToolBarImageList, hIcon);
			DeleteObject(hIcon);
		}
	}
	else { Message(L"Create an Image List with PresetToolBar() before calling this function."); }
}

// Preset status bar part count
void Standard_Window::PresetStatusBar(INT nParts)
{
	if (b_CreationComplete) { return; }
	if (nParts > 256) { nParts = 256; }
	m_StatusBarParts = nParts;
}

// Preset creation options that can override Style and Extended Style
void Standard_Window::PresetOptions(WindowOptions e_Options)
{
	if (b_CreationComplete) { return; }
	b_ToolBar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::ToolBar);
	b_StatusBar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::StatusBar);
	b_TextEditor = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::TextEditor);
	b_DialogBox = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Dialog);
	b_OpenGL = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::GL);
	b_DirectX = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::DX);
}