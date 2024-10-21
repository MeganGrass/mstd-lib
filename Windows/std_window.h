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

#include <resource.h>

#include "std_device.h"

#include <versionhelpers.h>

#include <dwmapi.h>


typedef class Standard_Window StdWin;

// IsWindows10OrGreater has been called?
static bool b_StdWinIsWindows10OrGreater = false;

// InitCommonControlsEx has been called?
static bool b_StdWinInitCommonControlsEx = false;


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
	Borderless = 1 << 30,				// Window will be borderless
	Fullscreen = 1 << 31,				// Window will be fullscreen on creation
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

	// Color
	COLORREF m_Color;									// Client Area Color
	bool b_ClassBrush;									// m_Class.hbrBackground will use m_Color? nullptr otherwise
	HBRUSH h_Brush;										// Brush

	// Accelerator Table
	HACCEL h_AccelTable;								// Accelerator Table Handle

	// Icon
	HICON h_Icon;										// Icon
	HICON h_IconSm;										// Small Icon

	// Cursor
	HCURSOR h_Cursor;									// Cursor

	// Menu
	HMENU h_Menu;										// Menu Handle
	UINT m_MenuID;										// Menu Resource ID

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
	bool b_CreationComplete;							// Window creation is complete?
	bool b_Borderless;									// Window has no borders, frames or title/caption bar?
	bool b_Fullscreen;									// Window is fullscreen?
	bool b_Help;										// Window has help icon?
	bool b_Menu;										// Window has menu?
	bool b_ToolBar;										// Window has toolbar?
	bool b_StatusBar;									// Window has status bar?
	bool b_TextEditor;									// Window has text editor?
	bool b_DialogBox;									// Window is a dialog box?
	bool b_ChildWindow;									// Window is a child window?
	bool b_OpenGL;										// Window has OpenGL rendering?
	bool b_DirectX;										// Window has Direct-X rendering?

	// Status
	bool b_IsActive;									// Window is active?
	bool b_HasFocus;									// Window has focus?

	// Child Windows
	std::vector<std::unique_ptr<Standard_Window>> v_ChildWindows;

	// Parse Window Creation and Style Options
	void ParsePresets(void);

	// Create Text Editor
	void CreateTextEditor(HWND hWndParent);

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
		m_Color(RGB(255, 255, 255)),
		b_ClassBrush(false),
		h_Brush(nullptr),
		h_AccelTable(nullptr),
		h_Icon(LoadIcon(0, IDI_APPLICATION)),
		h_IconSm(LoadIcon(0, IDI_APPLICATION)),
		h_Cursor(LoadCursor(0, IDC_ARROW)),
		h_Menu(nullptr),
		m_MenuID(0),
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
		b_CreationComplete(false),
		b_Borderless(false),
		b_Fullscreen(false),
		b_Help(false),
		b_Menu(false),
		b_ToolBar(false),
		b_StatusBar(false),
		b_TextEditor(false),
		b_DialogBox(false),
		b_ChildWindow(false),
		b_OpenGL(false),
		b_DirectX(false),
		b_IsActive(false),
		b_HasFocus(false)
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

		m_Class.cbSize = sizeof(WNDCLASSEXW);
	}

	// Deconstruction
	virtual ~Standard_Window(void) noexcept
	{
		ShowWindow(hWnd, SW_HIDE);

		s_DroppedFiles.clear();

		ClearChildWindows();

		if (h_Cursor) { DestroyCursor(h_Cursor); }
		
		if (h_Brush) { DeleteObject(h_Brush); }
		if (m_Class.hbrBackground) { DeleteObject(m_Class.hbrBackground); }

		if (h_ToolBar)
		{
			ImageList_Destroy(h_ToolBarImageList);
			DestroyWindow(h_ToolBar);
		}
		m_ToolbarButtons.clear();

		if (h_StatusBar) { DestroyWindow(h_StatusBar); }

		if (h_TextEditor) { DestroyWindow(h_TextEditor); }

		if (h_TextEditorFont) { DeleteObject(h_TextEditorFont); }

		if (h_Icon) { DestroyIcon(h_Icon); }

		if (h_IconSm) { DestroyIcon(h_IconSm); }

		if (h_AccelTable) { DestroyAcceleratorTable(h_AccelTable); }

		if (hWnd) { DestroyWindow(hWnd); }

		if (m_Class.hInstance) { UnregisterClassW(m_Class.lpszClassName, m_Class.hInstance); }
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
		m_Color(std::exchange(v.m_Color, RGB(255, 255, 255))),
		b_ClassBrush(std::exchange(v.b_ClassBrush, false)),
		h_Brush(std::exchange(v.h_Brush, nullptr)),
		h_AccelTable(std::exchange(v.h_AccelTable, nullptr)),
		h_Icon(std::exchange(v.h_Icon, nullptr)),
		h_IconSm(std::exchange(v.h_IconSm, nullptr)),
		h_Cursor(std::exchange(v.h_Cursor, nullptr)),
		h_Menu(std::exchange(v.h_Menu, nullptr)),
		m_MenuID(std::exchange(v.m_MenuID, 0)),
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
		b_CreationComplete(std::exchange(v.b_CreationComplete, false)),
		b_Borderless(std::exchange(v.b_Borderless, false)),
		b_Fullscreen(std::exchange(v.b_Fullscreen, false)),
		b_Help(std::exchange(v.b_Help, false)),
		b_Menu(std::exchange(v.b_Menu, false)),
		b_ToolBar(std::exchange(v.b_ToolBar, false)),
		b_StatusBar(std::exchange(v.b_StatusBar, false)),
		b_TextEditor(std::exchange(v.b_TextEditor, false)),
		b_DialogBox(std::exchange(v.b_DialogBox, false)),
		b_ChildWindow(std::exchange(v.b_ChildWindow, false)),
		b_OpenGL(std::exchange(v.b_OpenGL, false)),
		b_DirectX(std::exchange(v.b_DirectX, false)),
		b_IsActive(std::exchange(v.b_IsActive, false)),
		b_HasFocus(std::exchange(v.b_HasFocus, false))
	{}
	Standard_Window& operator = (Standard_Window&& v) noexcept { return *this = Standard_Window(std::move(v)); }

	// Is window creation complete?
	bool operator !() const { return !b_CreationComplete; }

	// Parse command line parameters
	void CommandLine(LPWSTR lpCmdLine);

	// Preset no window borders, frames or title/caption bar
	void PresetBorderless(bool Borderless);

	// Preset fullscreen window
	void PresetFullscreen(bool Fullscreen);

	// Preset window style
	void PresetStyle(DWORD Style);

	// Preset window extended style
	void PresetStyleEx(DWORD StyleEx);

	// Preset class style
	void PresetClassStyle(UINT ClassStyle);

	// Preset class name
	void PresetClassName(const StringW ClassName);

	// Preset window (caption) name
	void PresetWindowName(const StringW Name);

	// Preset class name from resource string table (wide string)
	void PresetClassName(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window name from resource string table (wide string)
	void PresetWindowName(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window client rect color
	void PresetWindowColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush = false);

	// Preset window icon
	void PresetIcon(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window icon
	void PresetIcon(HINSTANCE hInstance, const StringW Filename);

	// Preset window small icon
	void PresetIconSm(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window small icon
	void PresetIconSm(HINSTANCE hInstance, const StringW Filename);

	// Preset window cursor
	void PresetCursor(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window cursor
	void PresetCursor(HINSTANCE hInstance, const StringW Filename);

	// Preset HMENU
	void PresetMenu(HINSTANCE hInstance, WORD ResourceID);

	/*
		Preset toolbar
		- Use PresetAddToolBarIcon() after calling this function
	*/
	void PresetToolBar(UINT IconWidth, UINT IconHeight, std::vector<TBBUTTON> Buttons, DWORD Style = (TBSTYLE_TOOLTIPS | TBSTYLE_FLAT), DWORD StyleEx = TBSTYLE_EX_DOUBLEBUFFER);

	/*
		Preset toolbar icon
		- Use PresetToolBar() before calling this function
	*/
	void PresetAddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID);

	/*
		Preset toolbar icon
		- Use PresetToolBar() before calling this function
	*/
	void PresetAddToolBarIcon(HINSTANCE hInstance, const StringW Filename);

	// Preset status bar part count
	void PresetStatusBar(INT nParts, DWORD Style = SBARS_TOOLTIPS);

	// Preset creation options that can override Style and Extended Style
	void PresetOptions(WindowOptions e_Options);

	// Create parent window
	void Create(int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

	// Creation complete?
	bool CreationComplete(void) const { return b_CreationComplete; }

	// Create child window
	HWND CreateChild(int x, int y, int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc, DWORD Style, DWORD StyleEx, WindowOptions e_Options = WindowOptions::None);

	// Add child window
	bool AddChildWindow(HWND hWndChild, bool b_SnapToChild);

	// Clear child windows
	void ClearChildWindows(void);

	// Create Toolbar
	void CreateToolbar(DWORD Style = (TBSTYLE_TOOLTIPS | TBSTYLE_FLAT), DWORD StyleEx = TBSTYLE_EX_DOUBLEBUFFER, HIMAGELIST ImageList = nullptr, std::vector<TBBUTTON> Buttons = {});

	// Create Status Bar
	void CreateStatusBar(DWORD Style = SBARS_TOOLTIPS, INT PartCount = 1);

	/*
		Set status bar tooltip
		- Tooltip will only appear if the string is too large to fit in the status bar part
	*/
	void SetStatusBarTooltip(int iPart, const StringW Tooltip) const;

	// Status bar message
	void Status(int iPart, const String _Message, ...) const;

	// Status bar message
	void Status(int iPart, const StringW _Message, ...) const;

	// Get status bar string
	[[nodiscard]] StringW GetStatus(int iPart) const;

	// Status bar message
	void StatusPercent(int iPart, UINT iIndex, UINT iTotal) { Status(iPart, L"%0.0f%%", (((double)iIndex / (double)iTotal) * 100)); }

	// Create tooltip
	HWND CreateTooltip(HWND hWndParent, ULONG ResourceID, StringW Tooltip);

	// Resize to window
	bool ResizeToWindow(HWND hWndChild, bool b_Center = true);

	// Set accelerator table
	void SetAcceleratorTable(HINSTANCE hInstance, ULONG ResourceID);

	// Get accelerator table
	[[nodiscard]] HACCEL GetAcceleratorTable(void) const { return h_AccelTable; }

	// Get window handle
	[[nodiscard]] HWND GetHandle(void) const { return hWnd; }

	// Get instance handle
	[[nodiscard]] HINSTANCE GetInstance(void) const { return h_Instance; }

	// Get window color
	[[nodiscard]] COLORREF GetColor(void) const { return m_Color; }

	// Get window color brush
	[[nodiscard]] HBRUSH GetBrush(void) const { return h_Brush; }

	// Get class brush
	[[nodiscard]] HBRUSH GetClassBrush(void) const { return m_Class.hbrBackground; }

	// Get menu handle
	[[nodiscard]] HMENU GetMenu(void) const { return h_Menu; }

	// Get dropped files
	[[nodiscard]] StrVecW GetDroppedFiles(void) const { return s_DroppedFiles; }

	// Clear the dropped file list
	void ClearDroppedFiles(void) { s_DroppedFiles.clear(); }

	// Get child window count
	[[nodiscard]] std::size_t GetChildWindowCount(void) const { return v_ChildWindows.size(); }

	// Get child window
	[[nodiscard]] Standard_Window* GetChildWindow(UINT Index);

	// Is borderless?
	[[nodiscard]] bool IsBorderless(void) const { return b_Borderless; }

	// Is fullscreen?
	[[nodiscard]] bool IsFullscreen(void);

	// Is window active?
	[[nodiscard]] bool IsActive(void) const { return b_IsActive; }

	// Has window focus?
	[[nodiscard]] bool HasFocus(void) const { return b_HasFocus; }

	// Get window DPI scale factor
	[[nodiscard]] FLOAT GetScaleFactor(void) const { return static_cast<FLOAT>(m_WindowDPI) / USER_DEFAULT_SCREEN_DPI; }

	// Get window DPI scale factor by percentage
	[[nodiscard]] UINT GetScaleFactorByPercentage(void) const { return std::to_underlying(m_ScaleFactor); }

	// Disallow peek preview for the window when the mouse hovers over the window's thumbnail in the taskbar
	void DisallowPeek(BOOL OnOff);

	// Get disallow peek preview
	[[nodiscard]] BOOL GetDisallowPeek(void) const { return b_DisallowPeek; }

	// Prevent window from fading to glass sheet when peek is invoked
	void ExcludeFromPeek(BOOL OnOff);

	// Get exclude from peek
	[[nodiscard]] BOOL GetExcludeFromPeek(void) const { return b_ExcludeFromPeek; }

	// Set dark mode
	void SetDarkMode(BOOL OnOff);

	// Get dark mode
	[[nodiscard]] BOOL GetDarkMode(void) const { return b_DarkMode; }

	// Set round corner preference
	void SetRoundCorners(DWM_WINDOW_CORNER_PREFERENCE Preference);

	// Get round corner preference
	[[nodiscard]] DWM_WINDOW_CORNER_PREFERENCE GetRoundCorners(void) const { return m_RoundCorners; }

	/*
		Set border color

		From Microsoft:
			Specifying DWMWA_COLOR_NONE (value 0xFFFFFFFE) for the color will suppress the drawing of the window border. This makes it possible to have a rounded window with no border

			Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the border color
	*/
	void SetBorderColor(COLORREF Color);

	// Get border color
	[[nodiscard]] COLORREF GetBorderColor(void) const { return m_BorderColor; }

	// Set border color on lost focus
	void SetBorderColorOnLostFocus(COLORREF Color) { m_BorderColorLostFocus = Color; }

	// Get border color on lost focus
	[[nodiscard]] COLORREF GetBorderColorOnLostFocus(void) const { return m_BorderColorLostFocus; }

	/*
		Set caption color

		From Microsoft:
			Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the caption color
	*/
	void SetCaptionColor(COLORREF Color);

	// Get caption color
	[[nodiscard]] COLORREF GetCaptionColor(void) const { return m_CaptionColor; }

	// Set caption color on lost focus
	void SetCaptionColorOnLostFocus(COLORREF Color) { m_CaptionColorLostFocus = Color; }

	// Get caption color on lost focus
	[[nodiscard]] COLORREF GetCaptionColorOnLostFocus(void) const { return m_CaptionColorLostFocus; }

	/*
		Set text color

		From Microsoft:
			Specifying DWMWA_COLOR_DEFAULT (value 0xFFFFFFFF) for the color will reset the window back to using the system's default behavior for the caption text color
	*/
	void SetTextColor(COLORREF Color);

	// Get text color
	[[nodiscard]] COLORREF GetTextColor(void) const { return m_TextColor; }

	// Set backdrop type
	void SetBackdropType(DWM_SYSTEMBACKDROP_TYPE Type);

	// Get backdrop type
	[[nodiscard]] DWM_SYSTEMBACKDROP_TYPE GetBackdropType(void) const { return m_BackdropType; }

	// WM_ACTIVATE
	void MsgActivate(WPARAM wParam, LPARAM lParam);

	// WM_SETFOCUS
	void MsgSetFocus(WPARAM wParam, LPARAM lParam);

	// WM_KILLFOCUS
	void MsgKillFocus(WPARAM wParam, LPARAM lParam);

	// WM_WINDOWPOSCHANGED
	void MsgPositionChanged(WPARAM wParam, LPARAM lParam);

	// WM_DISPLAYCHANGE
	void MsgDisplayChange(WPARAM wParam, LPARAM lParam);

	// WM_INPUT_DEVICE_CHANGE
	void MsgInputDeviceChange(WPARAM wParam, LPARAM lParam);

	// WM_INPUT
	void MsgInput(WPARAM wParam, LPARAM lParam);

	// WM_MOUSEWHEEL
	void MsgMouseWheel(WPARAM wParam, LPARAM lParam);

	// WM_MOUSEHWHEEL
	void MsgMouseHWheel(WPARAM wParam, LPARAM lParam);

	// WM_DROPFILES
	void MsgDropFiles(WPARAM wParam, LPARAM lParam);

	// WM_DPICHANGED
	void MsgDpiChanged(WPARAM wParam, LPARAM lParam) const;

};