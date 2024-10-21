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


/*
	Parse command line parameters
*/
void Standard_Window::CommandLine(LPWSTR lpCmdLine)
{
	if (b_CreationComplete) { return; }
	StrVecW _Commandline = GetStrVec(lpCmdLine);
	for (auto& _Arg : _Commandline)
	{
		ToLower(_Arg);
		if ((_Arg == L"-b") || (_Arg == L"-borderless")) { b_Borderless = true; }
		if ((_Arg == L"-f") || (_Arg == L"-fullscreen")) { b_Fullscreen = true; }
	}
}


/*
	Preset no window borders, frames or title/caption bar
*/
void Standard_Window::PresetBorderless(bool Borderless)
{
	if (b_CreationComplete) { return; }
	b_Borderless = Borderless;
}


/*
	Preset fullscreen window mode
*/
void Standard_Window::PresetFullscreen(bool Fullscreen)
{
	if (b_CreationComplete) { return; }
	b_Fullscreen = Fullscreen;
}


/*
	Preset Window Style
*/
void Standard_Window::PresetStyle(DWORD Style)
{
	if (b_CreationComplete) { return; }
	m_Style = Style;
}


/*
	Preset Window Extended Style
*/
void Standard_Window::PresetStyleEx(DWORD StyleEx)
{
	if (b_CreationComplete) { return; }
	m_StyleEx = StyleEx;
}


/*
	Preset Class Style
*/
void Standard_Window::PresetClassStyle(UINT ClassStyle)
{
	if (b_CreationComplete) { return; }
	m_ClassStyle = ClassStyle;
}


/*
	Preset class name
*/
void Standard_Window::PresetClassName(const StringW ClassName)
{
	if (b_CreationComplete) { return; }
	s_ClassName = ClassName;
}


/*
	Preset window (caption) name
*/
void Standard_Window::PresetWindowName(const StringW Name)
{
	if (b_CreationComplete) { return; }
	s_Name = Name;
}


/*
	Preset class name from resource string table (wide string)
*/
void Standard_Window::PresetClassName(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	std::vector<wchar_t> ClassName(65535);
	if (LoadStringW(hInstance, ResourceID, ClassName.data(), static_cast<int>(ClassName.size())))
	{
		s_ClassName = ClassName.data();
	}
}


/*
	Preset window name from resource string table (wide string)
*/
void Standard_Window::PresetWindowName(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	std::vector<wchar_t> WindowName(65535);
	if (LoadStringW(hInstance, ResourceID, WindowName.data(), static_cast<int>(WindowName.size())))
	{
		s_Name = WindowName.data();
	}
}


/*
	Preset window client rect color
*/
void Standard_Window::PresetWindowColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush)
{
	if (b_CreationComplete) { return; }
	m_Color = RGB(Red, Green, Blue);
	h_Brush = CreateSolidBrush(m_Color);
	if (SetAsClassBrush) { b_ClassBrush = SetAsClassBrush; }
}


/*
	Preset window icon
*/
void Standard_Window::PresetIcon(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	h_Icon = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_Icon) { Message(L"An error occurred when trying to load the window icon."); }
}


/*
	Preset window icon
*/
void Standard_Window::PresetIcon(HINSTANCE hInstance, const StringW Filename)
{
	if (b_CreationComplete) { return; }
	h_Icon = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	if (!h_Icon) { Message(L"An error occurred when trying to load the window icon."); }
}


/*
	Preset window small icon
*/
void Standard_Window::PresetIconSm(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	h_IconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_IconSm) { Message(L"An error occurred when trying to load the window small icon."); }
}


/*
	Preset window small icon
*/
void Standard_Window::PresetIconSm(HINSTANCE hInstance, const StringW Filename)
{
	if (b_CreationComplete) { return; }
	h_IconSm = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	if (!h_IconSm) { Message(L"An error occurred when trying to load the window small icon."); }
}


/*
	Preset window cursor
*/
void Standard_Window::PresetCursor(HINSTANCE hInstance, ULONG ResourceID)
{
	if (b_CreationComplete) { return; }
	h_Cursor = LoadCursor(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_Cursor) { Message(L"An error occurred when trying to load the window cursor."); }
}


/*
	Preset window cursor
*/
void Standard_Window::PresetCursor(HINSTANCE hInstance, const StringW Filename)
{
	if (b_CreationComplete) { return; }
	h_Cursor = (HCURSOR)LoadImage(hInstance, Filename.c_str(), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	//h_Cursor = (HCURSOR)LoadImage(hInstance, Filename.c_str(), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	if (!h_Cursor) { Message(L"An error occurred when trying to load the window cursor."); }
}


/*
	Preset HMENU
*/
void Standard_Window::PresetMenu(HINSTANCE hInstance, WORD ResourceID)
{
	if (b_CreationComplete) { return; }
	h_Menu = LoadMenu(hInstance, MAKEINTRESOURCE(ResourceID));
	if (!h_Menu) { b_Menu = false; Message(L"An error occurred when trying to load the window menu."); }
	else { b_Menu = true; m_MenuID = ResourceID; }
}


/*
	Preset toolbar
*/
void Standard_Window::PresetToolBar(UINT IconWidth, UINT IconHeight, std::vector<TBBUTTON> Buttons, DWORD Style, DWORD StyleEx)
{
	if (h_ToolBarImageList) { ImageList_Destroy(h_ToolBarImageList); }
	if (!m_ToolbarButtons.empty()) { m_ToolbarButtons.clear(); }
	m_ToolBarIconWidth = IconWidth;
	m_ToolBarIconHeight = IconHeight;
	m_ToolbarButtons = Buttons;
	m_ToolBarStyle = Style;
	m_ToolBarStyleEx = StyleEx;
	h_ToolBarImageList = ImageList_Create(m_ToolBarIconWidth, m_ToolBarIconHeight, ILC_COLOR32 | ILC_MASK, static_cast<int>(Buttons.size()), 0);
}


/*
	Preset toolbar icon
*/
void Standard_Window::PresetAddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID)
{
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


/*
	Preset toolbar icon
*/
void Standard_Window::PresetAddToolBarIcon(HINSTANCE hInstance, const StringW Filename)
{
	if (h_ToolBarImageList)
	{
		HICON hIcon = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
		if (hIcon)
		{
			ImageList_AddIcon(h_ToolBarImageList, hIcon);
			DeleteObject(hIcon);
		}
	}
	else { Message(L"Create an Image List with PresetToolBar() before calling this function."); }
}


/*
	Preset status bar part count
*/
void Standard_Window::PresetStatusBar(INT nParts, DWORD Style)
{
	if (b_CreationComplete) { return; }
	if (nParts > 256) { nParts = 256; }
	m_StatusBarStyle = Style;
	m_StatusBarParts = nParts;
}


/*
	Preset creation options that can override Style and Extended Style on window creation
*/
void Standard_Window::PresetOptions(WindowOptions e_Options)
{
	if (b_CreationComplete) { return; }
	b_Borderless = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Borderless);
	b_Fullscreen = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Fullscreen);
	b_ToolBar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::ToolBar);
	b_StatusBar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::StatusBar);
	b_TextEditor = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::TextEditor);
	b_DialogBox = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Dialog);
	b_OpenGL = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::GL);
	b_DirectX = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::DX);
}


/*
	Set accelerator table
*/
void Standard_Window::SetAcceleratorTable(HINSTANCE hInstance, ULONG ResourceID)
{
	h_AccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_AccelTable) { Message(L"An error occurred when trying to load the window accelerator table."); }
}


/*
	Disallow peek
*/
void Standard_Window::DisallowPeek(BOOL OnOff)
{
	b_DisallowPeek = OnOff;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Peek Disallow Error: The parent window doesn't exist");
			return;
		}
		b_DisallowPeek = OnOff;
		DwmSetWindowAttribute(hWnd, DWMWA_DISALLOW_PEEK, &b_DisallowPeek, sizeof(BOOL));
	}
}


/*
	Exclude from Peek
*/
void Standard_Window::ExcludeFromPeek(BOOL OnOff)
{
	b_ExcludeFromPeek = OnOff;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Peek Exclude Error: The parent window doesn't exist");
			return;
		}
		b_ExcludeFromPeek = OnOff;
		DwmSetWindowAttribute(hWnd, DWMWA_EXCLUDED_FROM_PEEK, &b_ExcludeFromPeek, sizeof(BOOL));
	}
}


/*
	Set dark mode
*/
void Standard_Window::SetDarkMode(BOOL OnOff)
{
	b_DarkMode = OnOff;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Dark Mode Error: The parent window doesn't exist");
			return;
		}
		b_DarkMode = OnOff;
		DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &b_DarkMode, sizeof(BOOL));
	}
}


/*
	Set round corners
*/
void Standard_Window::SetRoundCorners(DWM_WINDOW_CORNER_PREFERENCE Preference)
{
	m_RoundCorners = Preference;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Round Corner Preference Error: The parent window doesn't exist");
			return;
		}
		m_RoundCorners = Preference;
		DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &m_RoundCorners, sizeof(DWM_WINDOW_CORNER_PREFERENCE));
	}
}


/*
	Set border color
*/
void Standard_Window::SetBorderColor(COLORREF Color)
{
	m_BorderColor = Color;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Window Border Color Error: The parent window doesn't exist");
			return;
		}
		m_BorderColor = Color;
		DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &m_BorderColor, sizeof(COLORREF));
	}
}


/*
	Set caption color
*/
void Standard_Window::SetCaptionColor(COLORREF Color)
{
	m_CaptionColor = Color;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Window Caption Color Error: The parent window doesn't exist");
			return;
		}
		m_CaptionColor = Color;
		DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &m_CaptionColor, sizeof(COLORREF));
	}
}


/*
	Set text color
*/
void Standard_Window::SetTextColor(COLORREF Color)
{
	m_TextColor = Color;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Window Text Color Error: The parent window doesn't exist");
			return;
		}
		m_TextColor = Color;
		DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &m_TextColor, sizeof(COLORREF));
	}
}


/*
	Set backdrop type
*/
void Standard_Window::SetBackdropType(DWM_SYSTEMBACKDROP_TYPE Type)
{
	m_BackdropType = Type;
	if (b_CreationComplete)
	{
		if (!hWnd)
		{
			Message(L"Window Backdrop Type Error: The parent window doesn't exist");
			return;
		}
		m_BackdropType = Type;
		DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &m_BackdropType, sizeof(DWM_SYSTEMBACKDROP_TYPE));
	}
}