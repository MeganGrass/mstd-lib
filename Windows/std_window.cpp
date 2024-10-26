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

#pragma comment(lib, "Dwmapi.lib")


/*
	Standard Window Message Handler
	- dwRefData is pointer to the Standard_Window object
*/
extern LRESULT CALLBACK StandardWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


/*
	Parse Window Creation and Style Options
*/
void Standard_Window::ParsePresets(WindowOptions e_Options)
{
	// Parse Window Creation Options
	b_TrueFullscreen = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::TrueFullscreen);
	b_Borderless = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Borderless);
	b_Fullscreen = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Fullscreen);
	b_Toolbar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::ToolBar);
	b_StatusBar = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::StatusBar);
	b_TextEditor = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::TextEditor);
	b_DialogBox = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::Dialog);
	b_OpenGL = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::GL);
	b_DirectX = std::to_underlying(e_Options) & std::to_underlying(WindowOptions::DX);

	// Force onto the Taskbar
	m_StyleEx |= WS_EX_APPWINDOW;

	// Minimize/Maximize
	if ((h_Menu) || (m_Style & WS_MINIMIZEBOX) || (m_Style & WS_MAXIMIZEBOX))
	{
		m_Style |= WS_SYSMENU;
		m_Style |= WS_CAPTION;
	}

	// Help
	if (m_StyleEx & WS_EX_CONTEXTHELP)
	{
		m_Style &= ~WS_MAXIMIZEBOX;
		m_Style &= ~WS_MINIMIZEBOX;
	}

	// Popup Window
	if (m_Style & WS_POPUP)
	{
		m_Style &= ~WS_CHILD;
	}

	// Child Window
	if (b_ChildWindow)
	{
		m_Style |= WS_CHILD;
		m_Style |= WS_CLIPSIBLINGS;
		m_Style &= ~WS_POPUP;
		m_Style &= ~WS_SYSMENU;
		//b_Menu = false;
	}

	// Borderless
	if (b_Borderless)
	{
		m_Style &= ~WS_CAPTION;
		m_Style &= ~WS_THICKFRAME;
		m_Style &= ~WS_MINIMIZEBOX;
		m_Style &= ~WS_MAXIMIZEBOX;
		m_Style &= ~WS_DLGFRAME;
		m_Style &= ~WS_BORDER;
		m_StyleEx &= ~WS_EX_DLGMODALFRAME;
		m_StyleEx &= ~WS_EX_CLIENTEDGE;
		m_StyleEx &= ~WS_EX_STATICEDGE;
		m_StyleEx &= ~WS_EX_WINDOWEDGE;
	}

}


/*
	Create Parent Window
*/
void Standard_Window::Create(int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc, WindowOptions e_Options)
{
	// Error
	if (hWnd)
	{
		Message(L"Create Window Error: The window already exists");
		return;
	}

	// Parse Window Styles
	ParsePresets(e_Options);

	// Copy Instance
	h_Instance = hInstance;

	// Window Class
	if (b_OpenGL) { m_ClassStyle |= CS_OWNDC; }
	m_Class.style = m_ClassStyle;

	m_Class.lpfnWndProc = WndProc;

	m_Class.cbClsExtra = 0;

	if (b_DialogBox) { m_Class.cbWndExtra = DLGWINDOWEXTRA; }
	else { m_Class.cbWndExtra = 0; }

	m_Class.hInstance = h_Instance;

	m_Class.hIcon = h_Icon;

	m_Class.hCursor = h_Cursor;

	if(b_ClassBrush) { m_Class.hbrBackground = CreateSolidBrush(m_Color); }
	else { m_Class.hbrBackground = nullptr; }
	
	if (h_Menu) { m_Class.lpszMenuName = MAKEINTRESOURCE(m_MenuID); }
	else { m_Class.lpszMenuName = nullptr; }

	m_Class.lpszClassName = s_ClassName.c_str();

	m_Class.hIconSm = h_IconSm;

	if (!RegisterClassExW(&m_Class)) { GetErrorMessage(); }

	// Get center window screen position
	int CxScreen = ((GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI) - Width) / 2);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }
	int CyScreen = ((GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI) - Height) / 2);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }

	// Fullscreen
	if (b_TrueFullscreen)
	{
		b_Fullscreen = true;
		CxScreen = 0;
		CyScreen = 0;
		Width = GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI);
		if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }
		Height = GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI);
		if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }
	}

	// Create
	hWnd = CreateWindowExW(
		m_StyleEx,
		s_ClassName.c_str(),
		s_Name.c_str(),
		m_Style,
		CxScreen, CyScreen,
		Width, Height,
		nullptr,
		h_Menu,
		h_Instance,
		nullptr);
	if (!hWnd) { GetErrorMessage(); }

	// Standard Window Message Handler
	SetWindowSubclass(hWnd, StandardWindowProc, 0, (DWORD_PTR)this);

	// Standard Windows Common Class
	SetCommonInstance(h_Instance);
	SetCommonOwner(hWnd);

	// Desktop Window Manager
	SetDisallowPeek(b_DisallowPeek);
	SetExcludeFromPeek(b_ExcludeFromPeek);
	SetDarkMode(b_DarkMode);
	SetRoundCorners(m_RoundCorners);
	SetBorderColor(m_BorderColor);
	SetCaptionColor(m_CaptionColor);
	SetTextColor(m_TextColor);
	SetBackdropType(m_BackdropType);

	// Borderless
	if (b_Borderless) { SetWindowLong(hWnd, GWL_STYLE, 0); }

	// Window size
	if (!b_TrueFullscreen)
	{
		RECT Rect{ 0, 0, Width, Height };

		// Toolbar
		if (b_Toolbar)
		{
			RECT ToolBarRect{};
			CreateToolbar(m_ToolBarStyle, m_ToolBarStyleEx, h_ToolBarImageList, m_ToolbarButtons);
			GetWindowRect(h_ToolBar, &ToolBarRect);
			Rect.bottom += (ToolBarRect.bottom - ToolBarRect.top);
		}

		// StatusBar
		if (b_StatusBar)
		{
			RECT StatusBarRect{};
			CreateStatusBar(m_StatusBarParts, m_StatusBarStyle);
			GetWindowRect(h_StatusBar, &StatusBarRect);
			Rect.bottom += (StatusBarRect.bottom - StatusBarRect.top);
		}

		// Adjust window size
		if (!AdjustWindowRectExForDpi(&Rect, GetStyle(), GetMenu(hWnd) ? TRUE : FALSE, GetStyleEx(), GetDPI())) { GetErrorMessage(); }

		SetWindowPos(hWnd, 0, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);
	}

	// Show Window
	b_Fullscreen ? ShowWindow(hWnd, SW_MAXIMIZE) : ShowWindow(hWnd, nCmdShow);

	// Update Window
	UpdateWindow(hWnd);
}


/*
	Create Child Window
*/
HWND Standard_Window::CreateChild(int x, int y, int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc, DWORD Style, DWORD StyleEx, WindowOptions e_Options)
{
	// Error
	if (!hWnd)
	{
		Message(L"Create Window Error: The parent window doesn't exist");
		return nullptr;
	}

	std::unique_ptr<Standard_Window> Window = std::make_unique<Standard_Window>();

	Window->b_ChildWindow = true;

	Window->m_Style = Style;
	Window->m_StyleEx = StyleEx;
	Window->SetCaptionName(s_Name + +L"_" + std::to_wstring(v_ChildWindows.size()));
	Window->PresetClassName(s_ClassName + L"_" + std::to_wstring(v_ChildWindows.size()));
	Window->SetColor((rand() % 255), (rand() % 255), (rand() % 255));
	Window->h_Brush = h_Brush;
	Window->h_Icon = h_Icon;
	Window->h_IconSm = h_IconSm;
	Window->h_Cursor = h_Cursor;
	Window->h_AccelTable = h_AccelTable;
	Window->m_SysDPI = m_SysDPI;
	Window->m_WindowDPI = m_WindowDPI;
	Window->m_ScaleFactor = m_ScaleFactor;

	WindowOptions FilteredOptions = WindowOptions::None;
	std::to_underlying(e_Options)& std::to_underlying(WindowOptions::Borderless) ? FilteredOptions | WindowOptions::Borderless : FilteredOptions;
	std::to_underlying(e_Options)& std::to_underlying(WindowOptions::Fullscreen) ? FilteredOptions | WindowOptions::Fullscreen : FilteredOptions;
	std::to_underlying(e_Options)& std::to_underlying(WindowOptions::Dialog) ? FilteredOptions | WindowOptions::Dialog : FilteredOptions;
	std::to_underlying(e_Options)& std::to_underlying(WindowOptions::GL) ? FilteredOptions | WindowOptions::GL : FilteredOptions;
	std::to_underlying(e_Options)& std::to_underlying(WindowOptions::DX) ? FilteredOptions | WindowOptions::DX : FilteredOptions;
	Window->ParsePresets(FilteredOptions);

	Window->h_Instance = hInstance;

	// Window Class
	if (Window->b_OpenGL) { Window->m_ClassStyle |= CS_OWNDC; }
	Window->m_Class.style = Window->m_ClassStyle;
	Window->m_Class.lpfnWndProc = WndProc;
	Window->m_Class.cbClsExtra = 0;
	if (Window->b_DialogBox) { Window->m_Class.cbWndExtra = DLGWINDOWEXTRA; }
	else { Window->m_Class.cbWndExtra = 0; }
	Window->m_Class.hInstance = hInstance;
	Window->m_Class.hIcon = Window->h_Icon;
	Window->m_Class.hCursor = Window->h_Cursor;
	if (Window->b_ClassBrush) { Window->m_Class.hbrBackground = CreateSolidBrush(Window->m_Color); }
	else { Window->m_Class.hbrBackground = nullptr; }
	if (Window->h_Menu) { Window->m_Class.lpszMenuName = MAKEINTRESOURCE(Window->m_MenuID); }
	else { Window->m_Class.lpszMenuName = nullptr; }
	Window->m_Class.lpszClassName = Window->s_ClassName.c_str();
	Window->m_Class.hIconSm = Window->h_IconSm;
	if (!RegisterClassExW(&Window->m_Class)) { GetErrorMessage(); }

	// Adjust window size and position
	RECT Rect{ 0, 0, Width, Height };

	if (!AdjustWindowRectExForDpi(&Rect, Window->m_Style, FALSE, Window->m_StyleEx, Window->m_WindowDPI)) { GetErrorMessage(); }

	if (h_ToolBar)
	{
		RECT ToolBarRect{};
		GetWindowRect(h_ToolBar, &ToolBarRect);
		y += (ToolBarRect.bottom - ToolBarRect.top);
	}

	// Create Window
	Window->hWnd = CreateWindowExW(
		Window->m_StyleEx,
		Window->s_ClassName.c_str(),
		Window->s_Name.c_str(),
		Window->m_Style,
		x, y,
		(Rect.right - Rect.left),
		(Rect.bottom - Rect.top),
		hWnd,
		nullptr,
		Window->h_Instance,
		nullptr);
	if (!Window->hWnd) { GetErrorMessage(); }

	// Standard Windows Common Class
	Window->SetCommonInstance(h_Instance);
	Window->SetCommonOwner(hWnd);

	// Desktop Window Manager
	Window->SetDarkMode(GetDarkMode());
	Window->SetRoundCorners(GetRoundCorners());
	Window->SetBorderColor(GetBorderColor());
	Window->SetBorderColorOnLostFocus(GetBorderColorOnLostFocus());
	Window->SetCaptionColor(GetCaptionColor());
	Window->SetCaptionColorOnLostFocus(GetCaptionColorOnLostFocus());
	Window->SetTextColor(GetTextColor());
	Window->SetTextColorOnLostFocus(GetTextColorOnLostFocus());
	Window->SetBackdropType(GetBackdropType());

	if (Window->b_Borderless) { SetWindowLong(Window->hWnd, GWL_STYLE, 0); }

	ShowWindow(Window->hWnd, nCmdShow);

	UpdateWindow(Window->hWnd);

	SetFocus(hWnd);

	v_ChildWindows.push_back(std::move(Window));

	return v_ChildWindows.back()->hWnd;
}


/*
	Add Child Window
*/
bool Standard_Window::AddChildWindow(HWND hWndChild, bool b_SnapToChild)
{
	// Error
	if (!hWnd)
	{
		Message(L"Add Window Error: The parent window doesn't exist");
		return false;
	}

	// Error
	if (!hWndChild)
	{
		Message(L"Create Window Error: The child window doesn't exist");
		return false;
	}

	std::unique_ptr<Standard_Window> Window = std::make_unique<Standard_Window>();

	if (b_SnapToChild)
	{
		Window->b_Borderless = true;

		RECT Rect{};
		GetClientRect(hWndChild, &Rect);

		SetWindowLong(hWndChild, GWL_STYLE, 0);
		SetWindowLong(hWndChild, GWL_EXSTYLE, 0);

		AdjustWindowRectExForDpi(&Rect, NULL, GetMenu(hWndChild) ? TRUE : FALSE, NULL, m_WindowDPI);

		SetWindowPos(hWndChild, 0, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

		Resize(&Rect, true);
	}

	Window->b_ChildWindow = true;

	Window->m_SysDPI = m_SysDPI;
	Window->m_WindowDPI = m_WindowDPI;
	Window->m_ScaleFactor = m_ScaleFactor;

	Window->ParsePresets(WindowOptions::None);

	Window->hWnd = hWndChild;

	// Standard Windows Common Class
	Window->SetCommonInstance(h_Instance);
	Window->SetCommonOwner(hWnd);

	// Desktop Window Manager
	Window->SetDarkMode(GetDarkMode());
	Window->SetRoundCorners(GetRoundCorners());
	Window->SetBorderColor(GetBorderColor());
	Window->SetBorderColorOnLostFocus(GetBorderColorOnLostFocus());
	Window->SetCaptionColor(GetCaptionColor());
	Window->SetCaptionColorOnLostFocus(GetCaptionColorOnLostFocus());
	Window->SetTextColor(GetTextColor());
	Window->SetTextColorOnLostFocus(GetTextColorOnLostFocus());
	Window->SetBackdropType(GetBackdropType());

	SetParent(Window->hWnd, hWnd);

	RECT Rect{};
	GetClientRect(hWnd, &Rect);

	int x = (rand() % Rect.right);
	int y = (rand() % Rect.bottom);

	if (b_SnapToChild)
	{
		x = 0;
		y = 0;
	}

	SetWindowPos(hWndChild, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	ShowWindow(Window->hWnd, SW_SHOW);

	UpdateWindow(Window->hWnd);

	SetFocus(hWnd);

	v_ChildWindows.push_back(std::move(Window));

	return true;
}


/*
	Get child window
*/
Standard_Window* Standard_Window::GetChildWindow(UINT Index)
{
	if (Index > (v_ChildWindows.size() - 1)) { return nullptr; }
	return v_ChildWindows.at(Index).get();
}


/*
	Clear child windows
*/
void Standard_Window::ClearChildWindows(void)
{
	for (auto& Child : v_ChildWindows)
	{
		Child.reset();
	}
	v_ChildWindows.clear();
}


/*
	Create tooltip
*/
HWND Standard_Window::CreateTooltip(HWND hWndParent, ULONG ResourceID, StringW Tooltip)
{
	// Error
	if (!IsWindow(hWndParent))	// IsWindow is not thread safe!
	{
		Message(L"Create Tooltip Error: The parent window doesn't exist");
		return nullptr;
	}

	// Error
	if (Tooltip.empty())
	{
		Message(L"Create Tooltip Error: The tooltip text is empty");
		return nullptr;
	}

	// Get the window of the control
	HWND hWndControl = GetDlgItem(hWndParent, ResourceID);
	if (!hWndControl) { GetErrorMessage(); }

	// Create tooltip
	HWND h_Tooltip = CreateWindowExW(
		0,
		TOOLTIPS_CLASS,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWndParent,
		0,
		h_Instance,
		0);
	if (!hWnd) { GetErrorMessage(); }

	// Associate the tooltip with the control
	TOOLINFO ToolInfo = { 0 };
	ToolInfo.cbSize = sizeof(ToolInfo);
	ToolInfo.hwnd = hWndParent;
	ToolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	ToolInfo.uId = (UINT_PTR)hWndControl;
	ToolInfo.lpszText = Tooltip.data();
	SendMessage(h_Tooltip, TTM_ADDTOOL, 0, (LPARAM)&ToolInfo);

	// Complete
	return h_Tooltip;
}


/*
	Create Toolbar
*/
void Standard_Window::CreateToolbar(DWORD Style, DWORD StyleEx, HIMAGELIST ImageList, std::vector<TBBUTTON> Buttons)
{
	if (!hWnd)
	{
		Message(L"Create Toolbar Error: The parent window doesn't exist");
		return;
	}

	if ((!ImageList) || (Buttons.empty()))
	{
		return;
	}

	Style &= (TBSTYLE_ALTDRAG | TBSTYLE_CUSTOMERASE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_REGISTERDROP | TBSTYLE_TOOLTIPS | TBSTYLE_TRANSPARENT | TBSTYLE_WRAPABLE);
	StyleEx &= (TBSTYLE_EX_DRAWDDARROWS | TBSTYLE_EX_HIDECLIPPEDBUTTONS | TBSTYLE_EX_DOUBLEBUFFER | TBSTYLE_EX_MIXEDBUTTONS | TBSTYLE_EX_MULTICOLUMN | TBSTYLE_EX_VERTICAL);

	h_ToolBar = CreateWindowExW(
		StyleEx,
		TOOLBARCLASSNAMEW,
		0,
		WS_CHILD | WS_VISIBLE | Style,
		0, 0,
		0, 0,
		hWnd,
		0,
		m_Class.hInstance,
		0);

	if (!h_ToolBar) { GetErrorMessage(); }

	SendMessage(h_ToolBar, TB_BUTTONSTRUCTSIZE, MAKEWPARAM(sizeof(TBBUTTON), 0), 0);

	SendMessage(h_ToolBar, TB_SETIMAGELIST, 0, (LPARAM)ImageList);

	SendMessage(h_ToolBar, TB_ADDBUTTONS, MAKEWPARAM(Buttons.size(), 0), (LPARAM)Buttons.data());

	SendMessage(h_ToolBar, TB_AUTOSIZE, 0, 0);

	SendMessage(h_ToolBar, WM_SIZE, 0, 0);
}


/*
	Create Status Bar
*/
void Standard_Window::CreateStatusBar(INT PartCount, DWORD Style)
{
	if (!hWnd)
	{
		Message(L"Create Status Bar Error: The parent window doesn't exist");
		return;
	}

	m_StatusBarParts = PartCount;

	if ((!m_StatusBarParts) || (m_StatusBarParts < 0)) { return; }

	if (m_StatusBarParts > 256) { m_StatusBarParts = 256; }

	Style &= (SBARS_SIZEGRIP | SBARS_TOOLTIPS);

	h_StatusBar = CreateWindowExW(
		0,
		STATUSCLASSNAMEW,
		0,
		WS_CHILD | WS_VISIBLE | Style,
		0, 0,
		0, 0,
		hWnd,
		0,
		m_Class.hInstance,
		0);

	if (!h_StatusBar) { GetErrorMessage(); }

	// Create Parts
	RECT ParentRect { };
	if (!GetClientRect(hWnd, &ParentRect)) { GetErrorMessage(); }

	SendMessage(h_StatusBar, WM_SIZE, 0, MAKELPARAM(ParentRect.right, ParentRect.bottom));

	std::vector<INT> Parts(m_StatusBarParts);

	LONG Width = ParentRect.right / m_StatusBarParts;

	INT RightEdge = Width;

	for (auto& Part : Parts)
	{
		Part = RightEdge;
		RightEdge += Width;
	}

	SendMessage(h_StatusBar, SB_SETPARTS, m_StatusBarParts, (LPARAM)Parts.data());
}


/*
	Set status bar tooltip
*/
void Standard_Window::SetStatusBarTooltip(int iPart, const StringW Tooltip) const
{
	if ((!h_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return; }

	SendMessageW(h_StatusBar, SB_SETTIPTEXTW, iPart, (LPARAM)Tooltip.c_str());
}


/*
	Status Bar Message
*/
void Standard_Window::Status(int iPart, const String _Message, ...) const
{
	// Error
	if ((!h_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return; }

	// Format
	std::va_list _ArgList;
	va_start(_ArgList, _Message);
	int _StrLen = (std::vsnprintf(0, 0, _Message.c_str(), _ArgList) + sizeof(char));
	std::vector<char> String(_StrLen);
	std::vsnprintf(String.data(), _StrLen, _Message.c_str(), _ArgList);
	va_end(_ArgList);

	// Set Text
	SendMessageA(h_StatusBar, SB_SETTEXTA, iPart, (LPARAM)String.data());
}


/*
	Status Bar Message
*/
void Standard_Window::Status(int iPart, const StringW _Message, ...) const
{
	// Error
	if ((!h_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return; }

	// Format
	std::va_list _ArgList;
	va_start(_ArgList, _Message);
	int _StrLen = (std::vswprintf(0, 0, _Message.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Message.c_str(), _ArgList);
	va_end(_ArgList);

	// Set Text
	SendMessageW(h_StatusBar, SB_SETTEXTW, iPart, (LPARAM)String.data());
}


/*
	Get status bar string
*/
StringW Standard_Window::GetStatus(int iPart) const
{
	if ((!h_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return L""; }

	std::size_t StrLen = static_cast<std::size_t>(SendMessageW(h_StatusBar, SB_GETTEXTLENGTHW, iPart, 0));

	StringW Buffer(StrLen + 1, 0);

	SendMessageW(h_StatusBar, SB_GETTEXTW, iPart, (LPARAM)Buffer.data());

	return Buffer;
}


/*
	Resize
*/
bool Standard_Window::Resize(RECT* Rect, bool b_Center)
{
	// Error
	if (!hWnd)
	{
		Message(L"Resize Window Error: The window doesn't exist");
		return false;
	}

	// Rect
	RECT _Rect = { Rect->left, Rect->top, Rect->right, Rect->bottom };

	// ToolBar
	if (h_ToolBar)
	{
		RECT ToolBarRect{};
		GetWindowRect(h_ToolBar, &ToolBarRect);
		_Rect.bottom += (ToolBarRect.bottom - ToolBarRect.top);
	}

	// StatusBar
	if (h_StatusBar)
	{
		RECT StatusBarRect{};
		GetWindowRect(h_StatusBar, &StatusBarRect);
		_Rect.bottom += (StatusBarRect.bottom - StatusBarRect.top);
	}

	// Adjust window size
	if (!AdjustWindowRectExForDpi(&_Rect, GetStyle(), GetMenu(hWnd) ? TRUE : FALSE, GetStyleEx(), GetDPI())) { GetErrorMessage(); }

	SetWindowPos(hWnd, 0, 0, 0, (_Rect.right - _Rect.left), (_Rect.bottom - _Rect.top), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	// Center Window
	if (b_Center)
	{
		const int CxScreen = ((GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI) - (_Rect.right - _Rect.left)) / 2);
		const int CyScreen = ((GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI) - (_Rect.bottom - _Rect.top)) / 2);
		SetWindowPos(hWnd, 0, CxScreen, CyScreen, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);
	}

	return true;
}


/*
	Is fullscreen?
*/
bool Standard_Window::IsFullscreen(void)
{
	QUERY_USER_NOTIFICATION_STATE m_FullscreenState;
	SHQueryUserNotificationState(&m_FullscreenState);
	switch (m_FullscreenState)
	{
	case QUNS_BUSY:
	case QUNS_RUNNING_D3D_FULL_SCREEN:
	case QUNS_PRESENTATION_MODE:
		return b_Fullscreen = true;
	default:
	case QUNS_NOT_PRESENT:
	case QUNS_ACCEPTS_NOTIFICATIONS:
	case QUNS_QUIET_TIME:
	case QUNS_APP:
		return b_Fullscreen = false;
	}
}