/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*		Completely redo creation of TextEditor
*		Preserve text from status bar when resizing
*
*/


#include "std_window.h"

// temp
#ifndef IDC_TOOLBAR_OPEN
#define IDC_TOOLBAR_OPEN IDC_STATIC
#endif

#ifndef IDC_TOOLBAR_CLOSE
#define IDC_TOOLBAR_CLOSE IDC_STATIC
#endif

#ifndef IDC_TOOLBAR_SAVE
#define IDC_TOOLBAR_SAVE IDC_STATIC
#endif

#ifndef IDC_TOOLBAR_NEW
#define IDC_TOOLBAR_NEW IDC_STATIC
#endif


/*
	Parse Window Creation and Style Options
*/
void Standard_Window::ParsePresets(void)
{
	// Force onto the Taskbar
	m_StyleEx |= WS_EX_APPWINDOW;

	// Minimize/Maximize
	if ((b_Menu) || (m_Style & WS_MINIMIZEBOX) || (m_Style & WS_MAXIMIZEBOX))
	{
		m_Style |= WS_SYSMENU;
		m_Style |= WS_CAPTION;
	}

	// Help
	if (m_StyleEx & WS_EX_CONTEXTHELP)
	{
		b_Help = true;
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
		b_Menu = false;
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
void Standard_Window::Create(int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc)
{
	// Error
	if (hWnd)
	{
		Message(L"Create Window Error: The parent window already exist");
		return;
	}

	// Parse Window Styles
	ParsePresets();

	// Copy Instance
	h_Instance = hInstance;

	// Register Window Class
	if (b_OpenGL) { m_ClassStyle |= CS_OWNDC; }
	m_Class.style = m_ClassStyle;
	m_Class.lpfnWndProc = WndProc;
	m_Class.cbClsExtra = 0;

	if (b_DialogBox) { m_Class.cbWndExtra = DLGWINDOWEXTRA; }
	else { m_Class.cbWndExtra = 0; }

	m_Class.hInstance = h_Instance;

	m_Class.hIcon = h_Icon;

	m_Class.hCursor = (HCURSOR)LoadImage(0, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

	if(b_ClassBrush) { m_Class.hbrBackground = CreateSolidBrush(m_Color); }
	else { m_Class.hbrBackground = nullptr; }
	
	if (b_Menu) { m_Class.lpszMenuName = MAKEINTRESOURCE(m_MenuID); }
	else { m_Class.lpszMenuName = nullptr; }

	m_Class.lpszClassName = s_ClassName.c_str();

	m_Class.hIconSm = h_IconSm;

	if (!RegisterClassExW(&m_Class)) { GetErrorMessage(); }

	// Width and Height
	m_Width = Width;
	m_Height = Height;

	// Fullscreen
	//if (b_Fullscreen)
	//{
	//	m_Width = GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI);
	//	m_Height = GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI);
	//}

	// Adjust window size and position
	RECT Rect{};
	Rect.left = 0;
	Rect.right = m_Width;
	Rect.top = 0;
	Rect.bottom = m_Height;

	if (!AdjustWindowRectExForDpi(&Rect, m_Style, b_Menu, m_StyleEx, m_SysDPI)) { GetErrorMessage(); }

	const int CxScreen = ((GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI) - m_Width) / 2);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }
	const int CyScreen = ((GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI) - m_Height) / 2);
	if (GetLastError() != ERROR_SUCCESS) { GetErrorMessage(); }

	// Create Window
	hWnd = CreateWindowExW(
		m_StyleEx,
		s_ClassName.c_str(),
		s_Name.c_str(),
		m_Style,
		CxScreen, CyScreen,
		(Rect.right - Rect.left),
		(Rect.bottom - Rect.top),
		nullptr,
		h_Menu,
		h_Instance,
		nullptr);
	if (!hWnd) { GetErrorMessage(); }

	// Standard Windows Common Class
	SetCommonInstance(h_Instance);
	SetCommonOwner(hWnd);

	// Borderless
	if (b_Borderless) { SetWindowLong(hWnd, GWL_STYLE, 0); }

	// ToolBar
	RECT ToolBarRect{};
	if (b_ToolBar)
	{
		CreateToolBar(hWnd);
		GetWindowRect(h_ToolBar, &ToolBarRect);
	}

	// StatusBar
	RECT StatusBarRect{};
	if (b_StatusBar)
	{
		CreateStatusBar(hWnd);
		GetWindowRect(h_StatusBar, &StatusBarRect);
	}

	// Text Editor
	if (b_TextEditor) { CreateTextEditor(hWnd); }

	// Adjust window size
	if (ToolBarRect.bottom - ToolBarRect.top) { Rect.bottom += (ToolBarRect.bottom - ToolBarRect.top); }
	if (StatusBarRect.bottom - StatusBarRect.top) { Rect.bottom += (StatusBarRect.bottom - StatusBarRect.top); }
	SetWindowPos(hWnd, 0, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	// Show Window
	if (b_Fullscreen)
	{
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	else
	{
		ShowWindow(hWnd, nCmdShow);
	}

	// Update Window
	UpdateWindow(hWnd);

	// Complete
	b_CreationComplete = true;
}


/*
	Create Parent Window
*/
HWND Standard_Window::CreateChild(int x, int y, int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc)
{
	// Error
	if (!hWnd)
	{
		Message(L"Create Window Error: The parent window doesn't exist");
		return nullptr;
	}

	std::unique_ptr<Standard_Window> Window = std::make_unique<Standard_Window>();

	Window->b_ChildWindow = true;
	Window->b_Borderless = true;
	Window->PresetWindowColor(255, 0, 255);
	Window->PresetClassName(s_ClassName + std::to_wstring(v_ChildWindows.size()));

	// Parse Window Styles
	Window->ParsePresets();

	// Copy Instance
	Window->h_Instance = hInstance;

	// Register Window Class
	if (Window->b_OpenGL) { Window->m_ClassStyle |= CS_OWNDC; }
	Window->m_Class.style = Window->m_ClassStyle;
	Window->m_Class.lpfnWndProc = WndProc;
	Window->m_Class.cbClsExtra = 0;
	if (Window->b_DialogBox) { Window->m_Class.cbWndExtra = DLGWINDOWEXTRA; }
	else { Window->m_Class.cbWndExtra = 0; }
	Window->m_Class.hInstance = hInstance;
	Window->m_Class.hIcon = Window->h_Icon;
	Window->m_Class.hCursor = (HCURSOR)LoadImage(0, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	if (Window->b_ClassBrush) { Window->m_Class.hbrBackground = CreateSolidBrush(Window->m_Color); }
	else { Window->m_Class.hbrBackground = nullptr; }
	if (Window->b_Menu) { Window->m_Class.lpszMenuName = MAKEINTRESOURCE(Window->m_MenuID); }
	else { Window->m_Class.lpszMenuName = nullptr; }
	Window->m_Class.lpszClassName = Window->s_ClassName.c_str();
	Window->m_Class.hIconSm = Window->h_IconSm;
	if (!RegisterClassExW(&Window->m_Class)) { GetErrorMessage(); }

	// Width and Height
	Window->m_Width = Width;
	Window->m_Height = Height;

	// Adjust window size and position
	RECT Rect{};
	Rect.left = 0;
	Rect.right = Window->m_Width;
	Rect.top = 0;
	Rect.bottom = Window->m_Height;

	if (!AdjustWindowRectExForDpi(&Rect, Window->m_Style, Window->b_Menu, Window->m_StyleEx, Window->m_SysDPI)) { GetErrorMessage(); }

	int CyScreen = y;
	if (b_ToolBar)
	{
		RECT ToolBarRect{};
		GetClientRect(h_ToolBar, &ToolBarRect);
		CyScreen += (ToolBarRect.bottom - ToolBarRect.top) + GetSystemMetricsForDpi(SM_CYEDGE, m_SysDPI);
	}

	// Create Window
	Window->hWnd = CreateWindowExW(
		Window->m_StyleEx,
		Window->s_ClassName.c_str(),	// NULL
		NULL,
		Window->m_Style,
		x, CyScreen,
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

	// Borderless
	if (Window->b_Borderless) { SetWindowLong(Window->hWnd, GWL_STYLE, 0); }

	// Show Window
	ShowWindow(Window->hWnd, nCmdShow);

	// Update Window
	UpdateWindow(Window->hWnd);

	// Setup Complete
	Window->b_CreationComplete = true;

	// Add to Child Windows
	v_ChildWindows.push_back(std::move(Window));

	// Set focus to the parent window
	SetFocus(hWnd);

	// Complete
	return v_ChildWindows.back()->hWnd;
}


/*
	Create Parent Window
*/
bool Standard_Window::AddChildWindow(HWND hWndChild, bool b_Borderless)
{
	// Error
	if (!hWnd)
	{
		Message(L"Create Window Error: The parent window doesn't exist");
		return false;
	}

	// Error
	if (!hWndChild)
	{
		Message(L"Create Window Error: The child window doesn't exist");
		return false;
	}

	std::unique_ptr<Standard_Window> Window = std::make_unique<Standard_Window>();

	Window->b_ChildWindow = true;
	Window->b_Borderless = b_Borderless;
	Window->PresetWindowColor(255, 0, 255);
	Window->PresetClassName(s_ClassName + std::to_wstring(v_ChildWindows.size()));

	// Parse Window Styles
	Window->ParsePresets();

	// Create Window
	Window->hWnd = hWndChild;

	// Standard Windows Common Class
	Window->SetCommonInstance(h_Instance);
	Window->SetCommonOwner(hWnd);

	// Borderless
	if (Window->b_Borderless) { SetWindowLong(Window->hWnd, GWL_STYLE, 0); }

	// Size and Position
	RECT ParentRect{};
	GetClientRect(hWnd, &ParentRect);

	RECT ChildRect{};
	GetClientRect(hWndChild, &ChildRect);

	int x = (ParentRect.right - ChildRect.right) / 2;
	int y = (ParentRect.bottom - ChildRect.bottom) / 2;

	if (!b_ToolBar) { y = 0; }
	if (!b_StatusBar)
	{
		if (b_ToolBar)
		{
			const int CySizeFrame = GetSystemMetricsForDpi(SM_CYFRAME, m_SysDPI) * 2;
			const int CyBorder = GetSystemMetricsForDpi(SM_CYBORDER, m_SysDPI) * 2;
			y += CySizeFrame;
			y += CyBorder;

			RECT ToolBarRect{};
			GetWindowRect(h_ToolBar, &ToolBarRect);
			AdjustWindowRectExForDpi(&ToolBarRect, NULL, false, NULL, m_SysDPI);
			y += ((ToolBarRect.bottom - ToolBarRect.top) / 4);
		}
	}
	else
	{
		if (b_ToolBar)
		{
			const int CyEdge = GetSystemMetricsForDpi(SM_CYEDGE, m_SysDPI) * 2;
			y += CyEdge;
		}
	}

	SetWindowPos(hWndChild, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	// Set Parent
	SetParent(Window->hWnd, hWnd);

	// Show Window
	ShowWindow(Window->hWnd, SW_SHOW);

	// Update Window
	UpdateWindow(Window->hWnd);

	// Setup Complete
	Window->b_CreationComplete = true;

	// Add to Child Windows
	v_ChildWindows.push_back(std::move(Window));

	// Set focus to the parent window
	SetFocus(hWnd);

	// Complete
	return true;
}


/*
	Resize to child window
*/
bool Standard_Window::ResizeToWindow(HWND hWndChild, bool b_Center)
{
	// Error
	if (!hWnd)
	{
		Message(L"Resize Window Error: The parent window doesn't exist");
		return false;
	}

	// Error
	if (!hWndChild)
	{
		Message(L"Resize Window Error: The child window doesn't exist");
		return false;
	}

	// Child Window Size
	RECT ChildRect{};
	GetClientRect(hWndChild, &ChildRect);

	// Adjust window size and position
	RECT Rect{};
	Rect.left = 0;
	Rect.right = ChildRect.right;
	Rect.top = 0;
	Rect.bottom = ChildRect.bottom;

	if (!AdjustWindowRectExForDpi(&Rect, m_Style, b_Menu, m_StyleEx, m_SysDPI)) { GetErrorMessage(); }

	// ToolBar
	RECT ToolBarRect{};
	if (b_ToolBar)
	{
		GetClientRect(h_ToolBar, &ToolBarRect);
	}

	// StatusBar
	RECT StatusBarRect{};
	if (b_StatusBar)
	{
		GetClientRect(h_StatusBar, &StatusBarRect);
	}

	// Adjust window size
	if (ToolBarRect.bottom - ToolBarRect.top) { Rect.bottom += (ToolBarRect.bottom - ToolBarRect.top); }
	if (StatusBarRect.bottom - StatusBarRect.top) { Rect.bottom += (StatusBarRect.bottom - StatusBarRect.top); }
	SetWindowPos(hWnd, 0, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);

	// Center Window
	if (b_Center)
	{
		const int CxScreen = ((GetSystemMetricsForDpi(SM_CXSCREEN, m_SysDPI) - (Rect.right - Rect.left)) / 2);
		const int CyScreen = ((GetSystemMetricsForDpi(SM_CYSCREEN, m_SysDPI) - (Rect.bottom - Rect.top)) / 2);
		SetWindowPos(hWnd, 0, CxScreen, CyScreen, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE | SWP_ASYNCWINDOWPOS);
	}

	// get client rect
	RECT ParentRect{};
	GetClientRect(hWnd, &ParentRect);
	m_Width = (ParentRect.right - ParentRect.left);
	m_Height = (ParentRect.bottom - ParentRect.top);

	return true;
}


/*
	Create tooltip
*/
HWND Standard_Window::CreateTooltip(HWND hWndParent, ULONG ResourceID, StringW Tooltip)
{
	// Error
	if (!IsWindow(hWndParent))
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

	// Get the window of the tool
	HWND hwndTool = GetDlgItem(hWndParent, ResourceID);
	if (!hwndTool)
	{
		Message(L"Create Tooltip Error: The resource item doesn't exist");
		return nullptr;
	}

	// Create the tooltip
	HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWndParent, NULL,
		h_Instance, NULL);
	if (!hwndTip)
	{
		Message(L"Create Tooltip Error: The tooltip window couldn't be created");
		return nullptr;
	}

	// Associate the tooltip with the tool
	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hWndParent;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hwndTool;
	toolInfo.lpszText = Tooltip.data();
	SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

	// Complete
	return hwndTip;
}


/*
	Create Tool Bar
*/
void Standard_Window::CreateToolBar(HWND hWndParent)
{
	// Error
	if ((!h_ToolBarImageList) ||
		(!m_ToolBarButtonCount) ||
		(!m_ToolBarIconWidth) ||
		(!m_ToolBarIconHeight)) { return; }

	// Create
	h_ToolBar = CreateWindowExW(
		TBSTYLE_EX_DOUBLEBUFFER,
		TOOLBARCLASSNAMEW,
		0,
		WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT,
		0, 0,
		0, 0,
		hWndParent,
		0,
		m_Class.hInstance,
		0);

	if (!h_ToolBar) { GetErrorMessage(); }

	// Parse Image List
	SendMessage(h_ToolBar, TB_BUTTONSTRUCTSIZE, MAKEWPARAM(sizeof(TBBUTTON), 0), 0);

	SendMessage(h_ToolBar, TB_SETIMAGELIST, 0, (LPARAM)h_ToolBarImageList);

	std::vector<TBBUTTON> tbButtons(m_ToolBarButtonCount);
	tbButtons[0] = { MAKELONG(0, 0), IDC_TOOLBAR_OPEN, TBSTATE_ENABLED, BTNS_AUTOSIZE | BTNS_SHOWTEXT, {}, 0, 0 };	// (INT_PTR)L"Open\0\0"
	tbButtons[1] = { MAKELONG(1, 0), IDC_TOOLBAR_CLOSE, TBSTATE_ENABLED, BTNS_AUTOSIZE, {}, 0, 0 };
	tbButtons[2] = { MAKELONG(2, 0), IDC_TOOLBAR_SAVE, TBSTATE_ENABLED, BTNS_AUTOSIZE, {}, 0, 0 };
	tbButtons[3] = { MAKELONG(3, 0), IDC_TOOLBAR_NEW, TBSTATE_ENABLED, BTNS_AUTOSIZE, {}, 0, 0 };

	SendMessage(h_ToolBar, TB_ADDBUTTONS, MAKEWPARAM(m_ToolBarButtonCount, 0), (LPARAM)tbButtons.data());

	SendMessage(h_ToolBar, TB_AUTOSIZE, 0, 0);

	SendMessage(h_ToolBar, WM_SIZE, 0, 0);

}


/*
	Create Status Bar
*/
void Standard_Window::CreateStatusBar(HWND hWndParent)
{
	// Error
	if ((!m_StatusBarParts) || (m_StatusBarParts < 0)) { return; }

	// Create
	h_StatusBar = CreateWindowExW(
		0,
		STATUSCLASSNAMEW,
		0,
		WS_CHILD | WS_VISIBLE,
		0, 0,
		0, 0,
		hWndParent,
		0,
		m_Class.hInstance,
		0);

	if (!h_StatusBar) { GetErrorMessage(); }

	// Create Parts
	RECT ParentRect { };
	if (!GetClientRect(hWndParent, &ParentRect)) { GetErrorMessage(); }

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

	SendMessage(h_StatusBar, SB_SETTEXTW, 0, (LPARAM)L"READY");

}


/*
	Create Text Editor
*/
void Standard_Window::CreateTextEditor(HWND hWndParent)
{
	// Parent Window Rect
	RECT Rect = { 0, 0, 0, 0 };
	if(!GetClientRect(hWndParent, &Rect)) { GetErrorMessage(); }

	// Style
	DWORD Style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

	// Window Position
	if (b_ToolBar) { Rect.top += (m_ToolBarIconHeight + 12); }
	if (b_StatusBar) { Rect.bottom -= 79; }

	// Create
	h_TextEditor = CreateWindowExW(
		WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE,
		WC_EDITW,
		(PTSTR)0,
		Style,
		Rect.left, Rect.top,
		Rect.right, Rect.bottom,
		hWndParent,
		0,
		m_Class.hInstance,
		0
	);

	if(!h_TextEditor) { GetErrorMessage(); }

	// Format
	h_TextEditorFont = CreateFont(32, 0, 0, 0,
		FW_NORMAL,				// Weight
		FALSE,					// Italic
		FALSE,					// Underline
		FALSE,					// Strikeout
		DEFAULT_CHARSET,		// CHAR Set
		OUT_OUTLINE_PRECIS,		// Output Precision
		CLIP_DEFAULT_PRECIS,	// Clip Precision
		CLEARTYPE_QUALITY,		// Quality
		MAKEWPARAM(VARIABLE_PITCH, FF_MODERN),
		TEXT("Courier New"));

	SendMessage(h_TextEditor, WM_SETFONT, (WPARAM)h_TextEditorFont, TRUE);
}


/*
	Status Bar Message
*/
void Standard_Window::Status(int iPart, const String _Message, ...)
{
	// Error
	if ((!b_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return; }

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
void Standard_Window::Status(int iPart, const StringW _Message, ...)
{
	// Error
	if ((!b_StatusBar) || (iPart > (m_StatusBarParts - 1))) { return; }

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