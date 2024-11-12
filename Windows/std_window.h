/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*
*/


#pragma once

#if MSTD_DEVICE
#include "std_device.h"
#else
#include "std_common.h"
#endif

#include <versionhelpers.h>

#include <dwmapi.h>

#include <shellscalingapi.h>


typedef class Standard_Window StdWin;
typedef class Windows_Devices StdWinDevices;

// IsWindows10OrGreater has been called?
static bool b_StdWinIsWindows10OrGreater = false;

// InitCommonControlsEx has been called?
static bool b_StdWinInitCommonControlsEx = false;

// Windows Devices have been initialized?
static bool b_StdWinDevicesInitialized = false;


/*
	Window Creation Options
*/
enum class WindowOptions : int
{
	//	Func Parameter					// Description
	ToolBar = 1 << 0,					// Window will have a toolbar
	StatusBar = 1 << 1,					// Window will have a status bar
	TextEditor = 1 << 2,				// Window will have a text editor
	Dialog = 1 << 3,					// Window will be a dialog box
	GL = 1 << 4,						// Window will have OpenGL rendering
	DX = 1 << 5,						// Window will have Direct-X rendering
	TrueFullscreen = 1 << 29,			// Window will be sized to the screen on creation
	Borderless = 1 << 30,				// Window will be borderless
	Fullscreen = 1 << 31,				// SW_MAXIMIZE will be used for ShowWindow
	None = 0							// Simple window will be created
};

static WindowOptions operator | (WindowOptions _Mode0, WindowOptions _Mode1)
{
	return static_cast<WindowOptions>(std::to_underlying(_Mode0) | std::to_underlying(_Mode1));
}


/*
	Standard Window
*/
class Standard_Window :
	public Standard_Windows_Common {
private:

	// Basic
	HWND hWnd;											// Handle
	HINSTANCE h_Instance;								// Instance
	DWORD m_Style;										// Style
	DWORD m_StyleEx;									// Extended Style
	StringW s_Name;										// Caption

	// Class
	WNDCLASSEXW m_Class;								// Class
	UINT m_ClassStyle;									// Class Style
	StringW s_ClassName;								// Class Name

	// Brush
	HBRUSH h_Brush;										// Brush
	COLORREF m_Color;									// Client Area Color
	bool b_ClassBrush;									// m_Class.hbrBackground will use m_Color? nullptr otherwise

	// Icon
	HICON h_Icon;										// Icon
	HICON h_IconSm;										// Small Icon

	// Cursor
	HCURSOR h_Cursor;									// Cursor

	// Menu
	HMENU h_Menu;										// Menu Handle
	UINT m_MenuID;										// Menu Resource ID

	// Accelerator Table
	HACCEL h_AccelTable;								// Accelerator Table Handle

	// Drag and Drop
	POINT m_DropPoint;									// Drag and Drop Position
	StrVecW s_DroppedFiles;								// Dropped File List

	// DPI
	UINT m_SysDPI;										// System DPI
	UINT m_WindowDPI;									// Window DPI
	DEVICE_SCALE_FACTOR m_ScaleFactor;					// Scale Factor

	// Desktop Window Manager
	BOOL b_DisallowPeek;								// Disallow Peek Preview
	BOOL b_ExcludeFromPeek;								// Exclude from Peek
	BOOL b_DarkMode;									// Dark Mode
	DWM_WINDOW_CORNER_PREFERENCE m_RoundCorners;		// Round Corners Preference
	COLORREF m_BorderColor;								// Border Color
	COLORREF m_BorderColorLostFocus;					// Border Color on Lost Focus
	COLORREF m_CaptionColor;							// Caption Color
	COLORREF m_CaptionColorLostFocus;					// Caption Color on Lost Focus
	COLORREF m_TextColor;								// Text Color
	COLORREF m_TextColorLostFocus;						// Text Color on Lost Focus
	DWM_SYSTEMBACKDROP_TYPE m_BackdropType;				// Backdrop Type

	// Toolbar
	HWND h_ToolBar;										// Toolbar Window Handle
	DWORD m_ToolBarStyle;								// Toolbar Style
	DWORD m_ToolBarStyleEx;								// Toolbar Extended Style
	UINT m_ToolBarIconWidth;							// Toolbar Icon Width
	UINT m_ToolBarIconHeight;							// Toolbar Icon Height
	HIMAGELIST h_ToolBarImageList;						// Toolbar Image List
	std::vector<TBBUTTON> m_ToolbarButtons;				// Toolbar Buttons

	// Status Bar
	HWND h_StatusBar;									// Status Bar Window Handle
	DWORD m_StatusBarStyle;								// Status Bar Style
	INT m_StatusBarParts;								// Status Bar Part Count

	// Text Editor
	HWND h_TextEditor;									// Text Editor Window Handle
	HFONT h_TextEditorFont;								// Text Editor Font

	// Window Creation Options
	bool b_TrueFullscreen;								// Window will be sized to the screen on creation?
	bool b_Borderless;									// Window will have no borders, frames or title/caption bar on creation?
	bool b_Toolbar;										// Window will have toolbar on creation?
	bool b_StatusBar;									// Window will have status bar on creation?
	bool b_TextEditor;									// Window will have text editor on creation?
	bool b_DialogBox;									// Window is a dialog box?
	bool b_ChildWindow;									// Window is a child window?
	bool b_OpenGL;										// Window has OpenGL rendering?
	bool b_DirectX;										// Window has Direct-X rendering?

	// Status
	bool b_IsActive;									// Window is active?
	bool b_HasFocus;									// Window has focus?
	bool b_Fullscreen;									// Window is fullscreen? Otherwise, SW_MAXIMIZE will be used for ShowWindow on creation?

#if MSTD_DEVICE
	// Windows Devices
	std::shared_ptr<Windows_Devices> m_Devices;
#endif

	// Child Windows
	std::vector<std::unique_ptr<Standard_Window>> v_ChildWindows;

	// Parse Window Creation and Style Options
	void ParsePresets(WindowOptions e_Options);

public:

	// Construction
	explicit Standard_Window(void) :
		hWnd(nullptr),
		h_Instance(nullptr),
		m_Style(0),
		m_StyleEx(0),
		s_Name(L"untitled"),
		m_Class{},
		m_ClassStyle(0),
		s_ClassName(L"untitled"),
		h_Brush(nullptr),
		m_Color(RGB(255, 255, 255)),
		b_ClassBrush(false),
		h_Icon(LoadIcon(0, IDI_APPLICATION)),
		h_IconSm(LoadIcon(0, IDI_APPLICATION)),
		h_Cursor(LoadCursor(0, IDC_ARROW)),
		h_Menu(nullptr),
		m_MenuID(0),
		h_AccelTable(nullptr),
		m_DropPoint{},
		m_SysDPI(GetDpiForSystem()),
		m_WindowDPI(GetDpiForSystem()),
		m_ScaleFactor(DEVICE_SCALE_FACTOR::SCALE_100_PERCENT),
		b_DisallowPeek(FALSE),
		b_ExcludeFromPeek(FALSE),
		b_DarkMode(TRUE),
		m_RoundCorners(DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT),
		m_BorderColor(RGB(76, 74, 72)),
		m_BorderColorLostFocus(RGB(48, 48, 48)),
		m_CaptionColor(RGB(32, 32, 32)),
		m_CaptionColorLostFocus(RGB(32, 32, 32)),
		m_TextColor(RGB(255, 255, 255)),
		m_TextColorLostFocus(RGB(255, 255, 255)),
		m_BackdropType(DWM_SYSTEMBACKDROP_TYPE::DWMSBT_MAINWINDOW),
		h_ToolBar(nullptr),
		m_ToolBarStyle(0),
		m_ToolBarStyleEx(0),
		m_ToolBarIconWidth(0),
		m_ToolBarIconHeight(0),
		h_ToolBarImageList(nullptr),
		h_StatusBar(nullptr),
		m_StatusBarStyle(0),
		m_StatusBarParts(0),
		h_TextEditor(nullptr),
		h_TextEditorFont(nullptr),
		b_TrueFullscreen(false),
		b_Borderless(false),
		b_Toolbar(false),
		b_StatusBar(false),
		b_TextEditor(false),
		b_DialogBox(false),
		b_ChildWindow(false),
		b_OpenGL(false),
		b_DirectX(false),
		b_IsActive(false),
		b_HasFocus(false),
		b_Fullscreen(false)
	{
		if (!b_StdWinIsWindows10OrGreater)
		{
			b_StdWinIsWindows10OrGreater = true;
			if (!IsWindows10OrGreater())
			{
				Message(L"Windows 10 or greater is required to run this application");
				std::exit(EXIT_SUCCESS);
			}
		}

		if (!b_StdWinInitCommonControlsEx)
		{
			b_StdWinInitCommonControlsEx = true;
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

#if MSTD_DEVICE
		if (!b_StdWinDevicesInitialized)
		{
			b_StdWinDevicesInitialized = true;
			m_Devices = std::make_shared<Windows_Devices>();
		}
#endif

		m_Class.cbSize = sizeof(WNDCLASSEXW);
	}

	// Deconstruction
	virtual ~Standard_Window(void) noexcept
	{
		if (hWnd) { ShowWindow(hWnd, SW_HIDE); }

		ClearChildWindows();

		if (h_Brush) { DeleteObject(h_Brush); }

		if (h_Icon) { DestroyIcon(h_Icon); }

		if (h_IconSm) { DestroyIcon(h_IconSm); }

		if (h_Cursor) { DestroyCursor(h_Cursor); }

		if (h_Menu) { DestroyMenu(h_Menu); }

		if (h_AccelTable) { DestroyAcceleratorTable(h_AccelTable); }

		if (h_ToolBar)
		{
			ImageList_Destroy(h_ToolBarImageList);
			DestroyWindow(h_ToolBar);
		}
		m_ToolbarButtons.clear();

		if (h_StatusBar) { DestroyWindow(h_StatusBar); }

		if (h_TextEditor) { DestroyWindow(h_TextEditor); }

		if (h_TextEditorFont) { DeleteObject(h_TextEditorFont); }

		if (hWnd) { DestroyWindow(hWnd); }

		if (m_Class.hInstance) { UnregisterClassW(m_Class.lpszClassName, m_Class.hInstance); }

		s_DroppedFiles.clear();
	}

	// Move
	Standard_Window(Standard_Window&& v) noexcept :
		hWnd(std::exchange(v.hWnd, nullptr)),
		h_Instance(std::exchange(v.h_Instance, nullptr)),
		m_Style(std::exchange(v.m_Style, 0)),
		m_StyleEx(std::exchange(v.m_StyleEx, 0)),
		s_Name(std::exchange(v.s_Name, L"")),
		m_Class(std::exchange(v.m_Class, WNDCLASSEX())),
		m_ClassStyle(std::exchange(v.m_ClassStyle, 0)),
		s_ClassName(std::exchange(v.s_ClassName, L"")),
		h_Brush(std::exchange(v.h_Brush, nullptr)),
		m_Color(std::exchange(v.m_Color, RGB(255, 255, 255))),
		b_ClassBrush(std::exchange(v.b_ClassBrush, false)),
		h_Icon(std::exchange(v.h_Icon, nullptr)),
		h_IconSm(std::exchange(v.h_IconSm, nullptr)),
		h_Cursor(std::exchange(v.h_Cursor, nullptr)),
		h_Menu(std::exchange(v.h_Menu, nullptr)),
		m_MenuID(std::exchange(v.m_MenuID, 0)),
		h_AccelTable(std::exchange(v.h_AccelTable, nullptr)),
		m_DropPoint(std::exchange(v.m_DropPoint, POINT{})),
		m_SysDPI(std::exchange(v.m_SysDPI, 0)),
		m_WindowDPI(std::exchange(v.m_WindowDPI, 0)),
		m_ScaleFactor(std::exchange(v.m_ScaleFactor, DEVICE_SCALE_FACTOR::SCALE_100_PERCENT)),
		b_DisallowPeek(std::exchange(v.b_DisallowPeek, FALSE)),
		b_ExcludeFromPeek(std::exchange(v.b_ExcludeFromPeek, FALSE)),
		b_DarkMode(std::exchange(v.b_DarkMode, TRUE)),
		m_RoundCorners(std::exchange(v.m_RoundCorners, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT)),
		m_BorderColor(std::exchange(v.m_BorderColor, RGB(76, 74, 72))),
		m_BorderColorLostFocus(std::exchange(v.m_BorderColorLostFocus, RGB(48, 48, 48))),
		m_CaptionColor(std::exchange(v.m_CaptionColor, RGB(32, 32, 32))),
		m_CaptionColorLostFocus(std::exchange(v.m_CaptionColorLostFocus, RGB(32, 32, 32))),
		m_TextColor(std::exchange(v.m_TextColor, RGB(255, 255, 255))),
		m_TextColorLostFocus(std::exchange(v.m_TextColorLostFocus, RGB(255, 255, 255))),
		m_BackdropType(std::exchange(v.m_BackdropType, DWM_SYSTEMBACKDROP_TYPE::DWMSBT_MAINWINDOW)),
		h_ToolBar(std::exchange(v.h_ToolBar, nullptr)),
		m_ToolBarStyle(std::exchange(v.m_ToolBarStyle, 0)),
		m_ToolBarStyleEx(std::exchange(v.m_ToolBarStyleEx, 0)),
		m_ToolBarIconWidth(std::exchange(v.m_ToolBarIconWidth, 0)),
		m_ToolBarIconHeight(std::exchange(v.m_ToolBarIconHeight, 0)),
		h_ToolBarImageList(std::exchange(v.h_ToolBarImageList, nullptr)),
		m_ToolbarButtons(std::exchange(v.m_ToolbarButtons, std::vector<TBBUTTON>())),
		h_StatusBar(std::exchange(v.h_StatusBar, nullptr)),
		m_StatusBarStyle(std::exchange(v.m_StatusBarStyle, 0)),
		m_StatusBarParts(std::exchange(v.m_StatusBarParts, 0)),
		h_TextEditor(std::exchange(v.h_TextEditor, nullptr)),
		h_TextEditorFont(std::exchange(v.h_TextEditorFont, nullptr)),
		b_TrueFullscreen(std::exchange(v.b_TrueFullscreen, false)),
		b_Borderless(std::exchange(v.b_Borderless, false)),
		b_Toolbar(std::exchange(v.b_Toolbar, false)),
		b_StatusBar(std::exchange(v.b_StatusBar, false)),
		b_TextEditor(std::exchange(v.b_TextEditor, false)),
		b_DialogBox(std::exchange(v.b_DialogBox, false)),
		b_ChildWindow(std::exchange(v.b_ChildWindow, false)),
		b_OpenGL(std::exchange(v.b_OpenGL, false)),
		b_DirectX(std::exchange(v.b_DirectX, false)),
		b_IsActive(std::exchange(v.b_IsActive, false)),
		b_HasFocus(std::exchange(v.b_HasFocus, false)),
		b_Fullscreen(std::exchange(v.b_Fullscreen, false))
	{}
	Standard_Window& operator = (Standard_Window&& v) noexcept { return *this = Standard_Window(std::move(v)); }

	/*
		Does the window exist?
	*/
	[[nodiscard]] operator bool() const { return hWnd; }

	/*
		Is the window active?
	*/
	[[nodiscard]] bool IsActive(void) const { return b_IsActive; }

	/*
		Does the window have focus?
	*/
	[[nodiscard]] bool HasFocus(void) const { return b_HasFocus; }

	/*
		Is the window fullscreen?
	*/
	[[nodiscard]] bool IsFullscreen(void);

	/*
		Drag and drop files available to be parsed?
	*/
	[[nodiscard]] bool DroppedFiles(void) { return !s_DroppedFiles.empty(); }

#if MSTD_DEVICE
	/*
		Windows Devices
	*/
	[[nodiscard]] std::shared_ptr<Windows_Devices> Device(void) const { return m_Devices; }
#endif

	/*
		Preset window style
		- intended to be called before Create()
	*/
	void PresetStyle(DWORD Style);

	/*
		Preset window extended style
		- intended to be called before Create()
	*/
	void PresetStyleEx(DWORD StyleEx);

	/*
		Preset class style
		- intended to be called before Create()
	*/
	void PresetClassStyle(UINT ClassStyle);

	/*
		Preset class name
		- intended to be called before Create()
	*/
	void PresetClassName(const StringW ClassName);

	/*
		Preset class name from resource string
		- intended to be called before Create()
	*/
	void PresetClassName(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Create parent window
	*/
	void Create(int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc, WindowOptions e_Options = WindowOptions::None);

	/*
		Create child window
	*/
	HWND CreateChild(int x, int y, int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc, DWORD Style, DWORD StyleEx, WindowOptions e_Options = WindowOptions::None);

	/*
		Add child window
		- if b_SnapToChild is true, the parent window will resize to fit the child window
		- if Size is not nullptr, the child window will be resized to the specified rect before the parent is snapped
	*/
	bool AddChildWindow(HWND hWndChild, int x, int y, bool b_SnapToChild, RECT* Size = nullptr);

	/*
		Empty the child window list
	*/
	void ClearChildWindows(void);

	/*
		Create tooltip
	*/
	HWND CreateTooltip(HWND hWndParent, ULONG ResourceID, StringW Tooltip);

	/*
		Set toolbar
		- use AddToolBarIcon() after calling this function
	*/
	void SetToolBar(UINT IconWidth, UINT IconHeight, std::vector<TBBUTTON> Buttons, DWORD Style = (TBSTYLE_TOOLTIPS | TBSTYLE_FLAT), DWORD StyleEx = TBSTYLE_EX_DOUBLEBUFFER);

	/*
		Preset toolbar icon
		- use SetToolBar() before calling this function
	*/
	void AddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Preset toolbar icon
		- use SetToolBar() before calling this function
	*/
	void AddToolBarIcon(HINSTANCE hInstance, const StringW Filename);

	/*
		Create Toolbar
	*/
	void CreateToolbar(DWORD Style = (TBSTYLE_TOOLTIPS | TBSTYLE_FLAT), DWORD StyleEx = TBSTYLE_EX_DOUBLEBUFFER, HIMAGELIST ImageList = nullptr, std::vector<TBBUTTON> Buttons = {});

	/*
		Set status bar style and part count
		- if called after Create(), CreateStatusBar() must be called prior to this function
		- if called after Create(), Style is ignored
	*/
	void SetStatusBar(INT nParts, DWORD Style = SBARS_TOOLTIPS);

	/*
		Create Status Bar
	*/
	void CreateStatusBar(INT PartCount = 1, DWORD Style = SBARS_TOOLTIPS);

	/*
		Set status bar tooltip
		- tooltip will only appear if the string is too large to fit in the status bar part
	*/
	void SetStatusBarTooltip(int iPart, const StringW Tooltip) const;

	/*
		Set status bar string
	*/
	void Status(int iPart, const String _Message, ...) const;

	/*
		Set status bar string
	*/
	void Status(int iPart, const StringW _Message, ...) const;

	/*
		Get status bar string
	*/
	[[nodiscard]] StringW GetStatus(int iPart) const;

	/*
		Status bar percentage message
	*/
	void SetStatusPercent(int iPart, UINT iIndex, UINT iTotal) const { Status(iPart, L"%0.0f%%", (((double)iIndex / (double)iTotal) * 100)); }

	/*
		Get rect
		- returns the client area rect, adjusted properly for the window's toolbar and status bar
	*/
	[[nodiscard]] RECT GetRect(void) const;

	/*
		Resize
	*/
	bool Resize(RECT* Rect, bool b_Center = true);

	/*
		Get window handle
	*/
	[[nodiscard]] HWND Get(void) const { return hWnd; }

	/*
		Get instance handle
	*/
	[[nodiscard]] HINSTANCE GetInstance(void) const { return h_Instance; }

	/*
		Get window style
	*/
	[[nodiscard]] DWORD GetStyle(void) { return m_Style = GetWindowLong(hWnd, GWL_STYLE); }

	/*
		Get window extended style
	*/
	[[nodiscard]] DWORD GetStyleEx(void) { return m_StyleEx = GetWindowLong(hWnd, GWL_EXSTYLE); }

	/*
		Set window name (caption string)
	*/
	void SetCaptionName(const StringW Name);

	/*
		Set window name (caption string) from resource string
	*/
	void SetCaptionName(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Get window name (caption string)
	*/
	[[nodiscard]] StringW GetCaptionName(void) const { return s_Name; }

	/*
		Get class name
	*/
	[[nodiscard]] StringW GetClassname(void) const { return s_ClassName; }

	/*
		Set window client rect color
		- can be called before or after Create(), but should be called at least once before
	*/
	void SetColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush = false);

	/*
		Get window client rect color
	*/
	[[nodiscard]] COLORREF GetColor(void) const { return m_Color; }

	/*
		Get brush
	*/
	[[nodiscard]] HBRUSH GetBrush(void) const { return h_Brush; }

	/*
		Get class brush
	*/
	[[nodiscard]] HBRUSH GetClassBrush(void) const { return m_Class.hbrBackground; }

	/*
		Set icon
	*/
	void SetIcon(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Set icon
	*/
	void SetIcon(HINSTANCE hInstance, const StringW Filename);

	/*
		Set small icon
	*/
	void SetIconSmall(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Set small icon
	*/
	void SetIconSmall(HINSTANCE hInstance, const StringW Filename);

	/*
		Set window cursor
	*/
	void SetCursor(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Set window cursor
	*/
	void SetCursor(HINSTANCE hInstance, const StringW Filename);

	/*
		Set menu
	*/
	void SetMenu(HINSTANCE hInstance, WORD ResourceID);

	/*
		Get menu handle
	*/
	[[nodiscard]] HMENU GetMenuHandle(void) { return h_Menu = GetMenu(hWnd); }

	/*
		Set accelerator table
	*/
	void SetAcceleratorTable(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Get accelerator table
	*/
	[[nodiscard]] HACCEL GetAcceleratorTable(void) const { return h_AccelTable; }

	/*
		Get DPI
	*/
	[[nodiscard]] UINT GetDPI(void) { return m_WindowDPI = GetDpiForWindow(hWnd); }

	/*
		Get system DPI
	*/
	[[nodiscard]] UINT GetSystemDPI(void) { return m_SysDPI = GetDpiForSystem(); }

	/*
		Get window DPI scale factor
	*/
	[[nodiscard]] FLOAT GetDpiScaleFactor(void) { return static_cast<FLOAT>(m_WindowDPI = GetDpiForWindow(hWnd)) / USER_DEFAULT_SCREEN_DPI; }

	/*
		Get device scale factor
	*/
	[[nodiscard]] DEVICE_SCALE_FACTOR GetDeviceScaleFactor(void);

	/*
		Get device scale factor by percentage
	*/
	[[nodiscard]] UINT GetDeviceScaleFactorPercentage(void) const { return std::to_underlying(m_ScaleFactor); }

	/*
		Disallow peek preview for the window when the mouse hovers over the window's thumbnail in the taskbar
	*/
	void SetDisallowPeek(BOOL OnOff);

	/*
		Get disallow peek preview
	*/
	[[nodiscard]] BOOL GetDisallowPeek(void) const { return b_DisallowPeek; }

	/*
		Prevent window from fading to glass sheet when peek is invoked
	*/
	void SetExcludeFromPeek(BOOL OnOff);

	/*
		Get exclude from peek
	*/
	[[nodiscard]] BOOL GetExcludeFromPeek(void) const { return b_ExcludeFromPeek; }

	/*
		Set dark mode
	*/
	void SetDarkMode(BOOL OnOff);

	/*
		Get dark mode
	*/
	[[nodiscard]] BOOL GetDarkMode(void) const { return b_DarkMode; }

	/*
		Set round corner preference
	*/
	void SetRoundCorners(DWM_WINDOW_CORNER_PREFERENCE Preference);

	/*
		Get round corner preference
	*/
	[[nodiscard]] DWM_WINDOW_CORNER_PREFERENCE GetRoundCorners(void) const { return m_RoundCorners; }

	/*
		Set border color

		- From Microsoft:
			- Specifying DWMWA_COLOR_NONE (value 0xFFFFFFFE) for the color will suppress the drawing of the window border. This makes it possible to have a rounded window with no border

			- Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the border color
	*/
	void SetBorderColor(COLORREF Color);

	/*
		Get border color
	*/
	[[nodiscard]] COLORREF GetBorderColor(void) const { return m_BorderColor; }

	/*
		Set border color on lost focus
	*/
	void SetBorderColorOnLostFocus(COLORREF Color) { m_BorderColorLostFocus = Color; }

	/*
		Get border color on lost focus
	*/
	[[nodiscard]] COLORREF GetBorderColorOnLostFocus(void) const { return m_BorderColorLostFocus; }

	/*
		Set caption color

		- From Microsoft: Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the caption color
	*/
	void SetCaptionColor(COLORREF Color);

	/*
		Get caption color
	*/
	[[nodiscard]] COLORREF GetCaptionColor(void) const { return m_CaptionColor; }

	/*
		Set caption color on lost focus
	*/
	void SetCaptionColorOnLostFocus(COLORREF Color) { m_CaptionColorLostFocus = Color; }

	/*
		Get caption color on lost focus
	*/
	[[nodiscard]] COLORREF GetCaptionColorOnLostFocus(void) const { return m_CaptionColorLostFocus; }

	/*
		Set text color

		- From Microsoft: Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the caption text color
	*/
	void SetTextColor(COLORREF Color);

	/*
		Get text color
	*/
	[[nodiscard]] COLORREF GetTextColor(void) const { return m_TextColor; }

	/*
		Set text color on lost focus
	*/
	void SetTextColorOnLostFocus(COLORREF Color) { m_TextColorLostFocus = Color; }

	/*
		Get text color on lost focus
	*/
	[[nodiscard]] COLORREF GetTextColorOnLostFocus(void) const { return m_TextColorLostFocus; }

	/*
		Set backdrop type
	*/
	void SetBackdropType(DWM_SYSTEMBACKDROP_TYPE Type);

	/*
		Get backdrop type
	*/
	[[nodiscard]] DWM_SYSTEMBACKDROP_TYPE GetBackdropType(void) const { return m_BackdropType; }

	/*
		Get dropped files
	*/
	[[nodiscard]] StrVecW GetDroppedFiles(void) const { return s_DroppedFiles; }

	/*
		Clear the dropped file list
	*/
	void ClearDroppedFiles(void) { s_DroppedFiles.clear(); }

	/*
		Get child window count
	*/
	[[nodiscard]] std::size_t GetChildWindowCount(void) const { return v_ChildWindows.size(); }

	/*
		Get child window
	*/
	[[nodiscard]] Standard_Window* GetChildWindow(UINT Index);

	/*
		Intended for use with WM_ACTIVATE
	*/
	void MsgActivate(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_SETFOCUS
	*/
	void MsgSetFocus(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_KILLFOCUS
	*/
	void MsgKillFocus(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_WINDOWPOSCHANGED
	*/
	void MsgPositionChanged(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_DISPLAYCHANGE
	*/
	void MsgDisplayChange(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_DROPFILES
	*/
	void MsgDropFiles(WPARAM wParam, LPARAM lParam);

	/*
		Intended for use with WM_DPICHANGED
	*/
	void MsgDpiChanged(WPARAM wParam, LPARAM lParam);

};