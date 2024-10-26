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
	Preset Window Style
*/
void Standard_Window::PresetStyle(DWORD Style)
{
	if (hWnd) { return; }
	m_Style = Style;
}


/*
	Preset Window Extended Style
*/
void Standard_Window::PresetStyleEx(DWORD StyleEx)
{
	if (hWnd) { return; }
	m_StyleEx = StyleEx;
}


/*
	Preset Class Style
*/
void Standard_Window::PresetClassStyle(UINT ClassStyle)
{
	if (hWnd) { return; }
	m_ClassStyle = ClassStyle;
}


/*
	Preset class name
*/
void Standard_Window::PresetClassName(const StringW ClassName)
{
	if (hWnd) { return; }
	s_ClassName = ClassName;
}


/*
	Preset class name from resource string
*/
void Standard_Window::PresetClassName(HINSTANCE hInstance, ULONG ResourceID)
{
	if (hWnd) { return; }
	std::vector<TCHAR> ClassName(65535);
	if (LoadString(hInstance, ResourceID, ClassName.data(), static_cast<int>(ClassName.size())))
	{
		s_ClassName = ClassName.data();
	}
}


/*
	Set status bar style and part count
*/
void Standard_Window::SetStatusBar(INT nParts, DWORD Style)
{
	if (nParts > 256) { nParts = 256; }

	m_StatusBarStyle = Style;

	m_StatusBarParts = nParts;

	if (h_StatusBar)
	{
		RECT Rect{};
		GetClientRect(hWnd, &Rect);

		SendMessage(h_StatusBar, WM_SIZE, 0, MAKELPARAM(Rect.right, Rect.bottom));

		std::vector<INT> Parts(m_StatusBarParts);
		LONG Width = Rect.right / m_StatusBarParts;
		INT RightEdge = Width;
		for (auto& Part : Parts)
		{
			Part = RightEdge;
			RightEdge += Width;
		}
		SendMessage(h_StatusBar, SB_SETPARTS, m_StatusBarParts, (LPARAM)Parts.data());
	}
}


/*
	Set toolbar
*/
void Standard_Window::SetToolBar(UINT IconWidth, UINT IconHeight, std::vector<TBBUTTON> Buttons, DWORD Style, DWORD StyleEx)
{
	if (h_ToolBarImageList) { ImageList_Destroy(h_ToolBarImageList); }
	if (!m_ToolbarButtons.empty()) { m_ToolbarButtons.clear(); }
	m_ToolBarIconWidth = IconWidth;
	m_ToolBarIconHeight = IconHeight;
	m_ToolbarButtons = Buttons;
	m_ToolBarStyle = Style;
	m_ToolBarStyleEx = StyleEx;
	h_ToolBarImageList = ImageList_Create(m_ToolBarIconWidth, m_ToolBarIconHeight, ILC_COLOR32 | ILC_MASK, static_cast<int>(Buttons.size()), 0);
	if (!h_ToolBarImageList) { Message(L"An error occurred when trying to create the window toolbar image list"); }
}


/*
	Add toolbar icon
*/
void Standard_Window::AddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID)
{
	if (h_ToolBarImageList)
	{
		HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ResourceID), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
		if (hIcon)
		{
			ImageList_AddIcon(h_ToolBarImageList, hIcon);
			DeleteObject(hIcon);
		}
		else { Message(L"An error occurred when trying to load the window toolbar icon resource (%d)", ResourceID); }
	}
	else { Message(L"Create an Image List with SetToolBar() before calling this function"); }
}


/*
	Add toolbar icon
*/
void Standard_Window::AddToolBarIcon(HINSTANCE hInstance, const StringW Filename)
{
	if (h_ToolBarImageList)
	{
		HICON hIcon = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
		if (hIcon)
		{
			ImageList_AddIcon(h_ToolBarImageList, hIcon);
			DeleteObject(hIcon);
		}
		else { Message(L"An error occurred when trying to load the window toolbar icon file \"%s\"", Filename.c_str()); }
	}
	else { Message(L"Create an Image List with SetToolBar() before calling this function"); }
}


/*
	Set window name (caption)
*/
void Standard_Window::SetCaptionName(const StringW Name)
{
	s_Name = Name;
	if (hWnd) { SetWindowText(hWnd, s_Name.c_str()); }
}


/*
	Set window name (caption) from resource string
*/
void Standard_Window::SetCaptionName(HINSTANCE hInstance, ULONG ResourceID)
{
	std::vector<TCHAR> WindowName(65535);
	if (LoadString(hInstance, ResourceID, WindowName.data(), static_cast<int>(WindowName.size())))
	{
		s_Name = WindowName.data();
		if (hWnd) { SetWindowText(hWnd, s_Name.c_str()); }
	}
}


/*
	Set window client rect color
*/
void Standard_Window::SetColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush)
{
	m_Color = RGB(Red, Green, Blue);

	if (h_Brush) { DeleteObject(h_Brush); }
	h_Brush = CreateSolidBrush(m_Color);

	if (SetAsClassBrush)
	{
		b_ClassBrush = SetAsClassBrush;
		if (hWnd)
		{
			DeleteObject(m_Class.hbrBackground);
			m_Class.hbrBackground = CreateSolidBrush(m_Color);
		}
	}

	if (hWnd)
	{
		InvalidateRgn(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		ValidateRgn(hWnd, NULL);
	}
}


/*
	Set accelerator table
*/
void Standard_Window::SetAcceleratorTable(HINSTANCE hInstance, ULONG ResourceID)
{
	if (h_AccelTable) { DestroyAcceleratorTable(h_AccelTable); }

	h_AccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_AccelTable) { Message(L"An error occurred when trying to load the window accelerator table"); }
}


/*
	Set window icon
*/
void Standard_Window::SetIcon(HINSTANCE hInstance, ULONG ResourceID)
{
	if (h_Icon) { DestroyIcon(h_Icon); }

	h_Icon = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_Icon) { return Message(L"An error occurred when trying to load the window icon"); }

	if (hWnd) { SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)h_Icon); }
}


/*
	Set window icon
*/
void Standard_Window::SetIcon(HINSTANCE hInstance, const StringW Filename)
{
	if (h_Icon) { DestroyIcon(h_Icon); }

	h_Icon = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	if (!h_Icon) { return Message(L"An error occurred when trying to load the window icon"); }

	if (hWnd) { SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)h_Icon); }
}


/*
	Set window small icon
*/
void Standard_Window::SetIconSmall(HINSTANCE hInstance, ULONG ResourceID)
{
	if (h_IconSm) { DestroyIcon(h_IconSm); }

	h_IconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_IconSm) { return Message(L"An error occurred when trying to load the window small icon"); }

	if (hWnd) { SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)h_IconSm); }
}


/*
	Set window small icon
*/
void Standard_Window::SetIconSmall(HINSTANCE hInstance, const StringW Filename)
{
	if (h_IconSm) { DestroyIcon(h_IconSm); }

	h_IconSm = (HICON)LoadImage(hInstance, Filename.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	if (!h_IconSm) { return Message(L"An error occurred when trying to load the window small icon"); }

	if (hWnd) { SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)h_IconSm); }
}


/*
	Set window cursor
*/
void Standard_Window::SetCursor(HINSTANCE hInstance, ULONG ResourceID)
{
	if (h_Cursor) { DestroyCursor(h_Cursor); }

	h_Cursor = LoadCursor(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_Cursor) { Message(L"An error occurred when trying to load the window cursor"); }
}


/*
	Set window cursor
*/
void Standard_Window::SetCursor(HINSTANCE hInstance, const StringW Filename)
{
	if (h_Cursor) { DestroyCursor(h_Cursor); }

	h_Cursor = (HCURSOR)LoadImage(hInstance, Filename.c_str(), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_DEFAULTCOLOR | LR_LOADFROMFILE);	// LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	if (!h_Cursor) { Message(L"An error occurred when trying to load the window cursor"); }
}


/*
	Set menu
*/
void Standard_Window::SetMenu(HINSTANCE hInstance, WORD ResourceID)
{
	m_MenuID = ResourceID;

	if (h_Menu) { DestroyMenu(h_Menu); }

	h_Menu = LoadMenu(hInstance, MAKEINTRESOURCE(ResourceID));

	if (!h_Menu)
	{
		m_MenuID = 0;
		Message(L"An error occurred when trying to load the window menu");
	}
}


/*
	Get scale factor
*/
DEVICE_SCALE_FACTOR Standard_Window::GetDeviceScaleFactor(void)
{
	GetScaleFactorForMonitor(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &m_ScaleFactor);
	return m_ScaleFactor;
}


/*
	Disallow peek
*/
void Standard_Window::SetDisallowPeek(BOOL OnOff)
{
	b_DisallowPeek = OnOff;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_DISALLOW_PEEK, &b_DisallowPeek, sizeof(BOOL)); }
}


/*
	Exclude from Peek
*/
void Standard_Window::SetExcludeFromPeek(BOOL OnOff)
{
	b_ExcludeFromPeek = OnOff;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_EXCLUDED_FROM_PEEK, &b_ExcludeFromPeek, sizeof(BOOL)); }
}


/*
	Set dark mode
*/
void Standard_Window::SetDarkMode(BOOL OnOff)
{
	b_DarkMode = OnOff;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &b_DarkMode, sizeof(BOOL)); }
}


/*
	Set round corners
*/
void Standard_Window::SetRoundCorners(DWM_WINDOW_CORNER_PREFERENCE Preference)
{
	m_RoundCorners = Preference;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &m_RoundCorners, sizeof(DWM_WINDOW_CORNER_PREFERENCE)); }
}


/*
	Set border color
*/
void Standard_Window::SetBorderColor(COLORREF Color)
{
	m_BorderColor = Color;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &m_BorderColor, sizeof(COLORREF)); }
}


/*
	Set caption color
*/
void Standard_Window::SetCaptionColor(COLORREF Color)
{
	m_CaptionColor = Color;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &m_CaptionColor, sizeof(COLORREF)); }
}


/*
	Set text color
*/
void Standard_Window::SetTextColor(COLORREF Color)
{
	m_TextColor = Color;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &m_TextColor, sizeof(COLORREF)); }
}


/*
	Set backdrop type
*/
void Standard_Window::SetBackdropType(DWM_SYSTEMBACKDROP_TYPE Type)
{
	m_BackdropType = Type;
	if (hWnd) { DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &m_BackdropType, sizeof(DWM_SYSTEMBACKDROP_TYPE)); }
}