/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*		LoadImageW for preset loading icons
*		Change toolbar to rebar?
*		WM_SIZE is being called on boot
*		Add more #pragma libraries
*		Maybe change nCmdShow to SW_SHOWDEFAULT in main.cpp
* 
* 
*		if Create Width/Height is 0 or too large, fix it
* 
*		LoadCursor options?
* 
*		Fix all instance variables
* 
*		Complete imagelist creation -- add function to add icons to imagelist
* 
*		Better descriptions for functions
* 
*		Command console
* 
*		Users
*
*/


#pragma once

#include <resource.h>

#include "std_system.h"

#include "std_device.h"


typedef class Standard_Window StdWin;


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
	DX = 1 << 5,						// Window will have a Direct-X child window
	None = 0							// Generic Window will be created
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

	// Parent Window
	HWND hWnd;							// Window Handle
	HINSTANCE h_Instance;				// Instance
	StringW s_Name;						// Window Name
	POINT m_DropPoint;					// Drag and Drop Position

	// Status
	bool b_CreationComplete;			// Window creation is complete?
	bool b_IsActive;					// Window is active?
	bool b_HasFocus;					// Window has focus?

	// Style
	DWORD m_Style;						// Window Style
	DWORD m_StyleEx;					// Window Extended Style
	bool b_Borderless;					// Window has no borders, frames or title/caption bar?

	// Class
	WNDCLASSEXW m_Class;				// Window Class
	UINT m_ClassStyle;					// Window Class Style
	StringW s_ClassName;				// Window Class Name

	// Color
	COLORREF m_Color;					// Window Color
	bool b_ClassBrush;					// m_Class.hbrBackground will use m_Color? nullptr otherwise
	HBRUSH h_Brush;						// Window Brush

	// Accelerator Table
	HACCEL h_AccelTable;				// Accelerator Table Handle

	// DPI
	UINT m_SysDPI;						// System DPI
	UINT m_WindowDPI;					// Window DPI
	DEVICE_SCALE_FACTOR m_ScaleFactor;	// Scale Factor

	// Window Size
	INT m_Width;						// Window Width
	INT m_Height;						// Window Height
	bool b_Fullscreen;					// Window is fullscreen?

	// Window Creation Options
	bool b_Help;						// Window has help icon?
	bool b_Menu;						// Window has menu?
	bool b_ToolBar;						// Window has toolbar?
	bool b_StatusBar;					// Window has status bar?
	bool b_TextEditor;					// Window has text editor?
	bool b_DialogBox;					// Window is a dialog box?
	bool b_ChildWindow;					// Window is a child window?
	bool b_OpenGL;						// Window has OpenGL rendering?
	bool b_DirectX;						// Window has a Direct-X child window?

	// Icon
	HICON h_Icon;						// Window Icon
	HICON h_IconSm;						// Window Small Icon

	// Menu
	HMENU h_Menu;						// Menu Handle
	UINT m_MenuID;						// Menu Resource ID

	// Toolbar
	HWND h_ToolBar;						// Tool Bar Window Handle
	UINT m_ToolBarButtonCount;			// Tool Bar Button Count
	UINT m_ToolBarIconWidth;			// Tool Bar Icon Width
	UINT m_ToolBarIconHeight;			// Tool Bar Icon Height
	HIMAGELIST h_ToolBarImageList;		// Tool Bar Image List

	// Status Bar
	HWND h_StatusBar;					// Status Bar Window Handle
	INT m_StatusBarParts;				// Status Bar Part Count

	// Text Editor
	HWND h_TextEditor;					// Text Editor Window Handle
	HFONT h_TextEditorFont;				// Text Editor Font

	// Child Windows
	std::vector<std::unique_ptr<Standard_Window>> v_ChildWindows;

	// Drag and Drop
	StrVecW DroppedFiles;				// Dropped File List

	// Parse Window Creation and Style Options
	void ParsePresets(void);

	// Create Tool Bar
	void CreateToolBar(HWND hWndParent);

	// Create Status Bar
	void CreateStatusBar(HWND hWndParent);

	// Create Text Editor
	void CreateTextEditor(HWND hWndParent);

public:

	// Construction
	explicit Standard_Window(void) :
		h_Instance(nullptr),
		s_Name(L"Untitled"),
		m_DropPoint{},
		b_CreationComplete(false),
		b_IsActive(false),
		b_HasFocus(false),
		m_Style(0),
		m_StyleEx(0),
		b_Borderless(false),
		m_Class{},
		m_ClassStyle(0),
		s_ClassName(L"Untitled"),
		m_Color(RGB(255, 255, 255)),
		b_ClassBrush(false),
		h_Brush(nullptr),
		h_AccelTable(nullptr),
		m_SysDPI(GetDpiForSystem()),
		m_WindowDPI(GetDpiForSystem()),
		m_ScaleFactor(DEVICE_SCALE_FACTOR::SCALE_100_PERCENT),
		m_Width(720),
		m_Height(480),
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
		h_Icon(LoadIcon(0, IDI_APPLICATION)),
		h_IconSm(LoadIcon(0, IDI_APPLICATION)),
		h_Menu(nullptr),
		m_MenuID(0),
		h_ToolBar(nullptr),
		m_ToolBarButtonCount(0),
		m_ToolBarIconWidth(0),
		m_ToolBarIconHeight(0),
		h_ToolBarImageList(nullptr),
		h_StatusBar(nullptr),
		m_StatusBarParts(2),
		h_TextEditor(nullptr),
		h_TextEditorFont(nullptr),
		hWnd(nullptr)
	{
		m_Class.cbSize = sizeof(WNDCLASSEXW);
	}

	// Deconstruction
	virtual ~Standard_Window(void) noexcept
	{
		ShowWindow(hWnd, SW_HIDE);

		// Clean dropped files
		DroppedFiles.clear();

		// Destroy Child Windows
		for (auto& Child : v_ChildWindows)
		{
			if (Child.get()->GetHandle())
			{
				DestroyWindow(Child.get()->GetHandle());
			}
			Child.reset();
		}
		
		// Destroy Brushes
		if (h_Brush) { DeleteObject(h_Brush); }
		if (m_Class.hbrBackground) { DeleteObject(m_Class.hbrBackground); }

		// Destroy Tool Bar
		if (h_ToolBar)
		{
			ImageList_Destroy(h_ToolBarImageList);
			DestroyWindow(h_ToolBar);
		}

		// Destroy Status Bar
		if (h_StatusBar) { DestroyWindow(h_StatusBar); }

		// Destroy Text Editor
		if (h_TextEditor) { DestroyWindow(h_TextEditor); }

		// Delete Font
		if (h_TextEditorFont) { DeleteObject(h_TextEditorFont); }

		// Delete Icon
		if (h_Icon) { DestroyIcon(h_Icon); }

		// Delete Small Icon
		if (h_IconSm) { DestroyIcon(h_IconSm); }

		// Delete Accelerator Table
		if (h_AccelTable) { DestroyAcceleratorTable(h_AccelTable); }

		// Destroy Window
		if (hWnd) { DestroyWindow(hWnd); }

		// Unregister Class
		if (m_Class.hInstance) { UnregisterClassW(m_Class.lpszClassName, m_Class.hInstance); }
	}

	/*
		Move
	*/
	Standard_Window(Standard_Window&& v) noexcept :
		hWnd(std::exchange(v.hWnd, nullptr)),
		h_Instance(std::exchange(v.h_Instance, nullptr)),
		s_Name(std::exchange(v.s_Name, L"")),
		m_DropPoint(std::exchange(v.m_DropPoint, POINT{})),
		b_CreationComplete(std::exchange(v.b_CreationComplete, false)),
		b_IsActive(std::exchange(v.b_IsActive, false)),
		b_HasFocus(std::exchange(v.b_HasFocus, false)),
		m_Style(std::exchange(v.m_Style, 0)),
		m_StyleEx(std::exchange(v.m_StyleEx, 0)),
		b_Borderless(std::exchange(v.b_Borderless, false)),
		m_Class(std::exchange(v.m_Class, WNDCLASSEX())),
		m_ClassStyle(std::exchange(v.m_ClassStyle, 0)),
		s_ClassName(std::exchange(v.s_ClassName, L"")),
		m_Color(std::exchange(v.m_Color, RGB(255, 255, 255))),
		b_ClassBrush(std::exchange(v.b_ClassBrush, false)),
		h_Brush(std::exchange(v.h_Brush, nullptr)),
		h_AccelTable(std::exchange(v.h_AccelTable, nullptr)),
		m_SysDPI(std::exchange(v.m_SysDPI, 0)),
		m_WindowDPI(std::exchange(v.m_WindowDPI, 0)),
		m_ScaleFactor(std::exchange(v.m_ScaleFactor, DEVICE_SCALE_FACTOR::SCALE_100_PERCENT)),
		m_Width(std::exchange(v.m_Width, 0)),
		m_Height(std::exchange(v.m_Height, 0)),
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
		h_Icon(std::exchange(v.h_Icon, nullptr)),
		h_IconSm(std::exchange(v.h_IconSm, nullptr)),
		h_Menu(std::exchange(v.h_Menu, nullptr)),
		m_MenuID(std::exchange(v.m_MenuID, 0)),
		h_ToolBar(std::exchange(v.h_ToolBar, nullptr)),
		m_ToolBarButtonCount(std::exchange(v.m_ToolBarButtonCount, 0)),
		m_ToolBarIconWidth(std::exchange(v.m_ToolBarIconWidth, 0)),
		m_ToolBarIconHeight(std::exchange(v.m_ToolBarIconHeight, 0)),
		h_ToolBarImageList(std::exchange(v.h_ToolBarImageList, nullptr)),
		h_StatusBar(std::exchange(v.h_StatusBar, nullptr)),
		m_StatusBarParts(std::exchange(v.m_StatusBarParts, 0)),
		h_TextEditor(std::exchange(v.h_TextEditor, nullptr)),
		h_TextEditorFont(std::exchange(v.h_TextEditorFont, nullptr)) {}
	Standard_Window& operator = (Standard_Window&& v) noexcept { return *this = Standard_Window(std::move(v)); }

	// Preset command line parameters
	void PresetCommandLine(LPWSTR lpCmdLine);

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

	// Preset window name
	void PresetWindowName(const StringW Name);

	// Preset class name from resource string table (wide string)
	void PresetClassName(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window name from resource string table (wide string)
	void PresetWindowName(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window client rect color
	void PresetWindowColor(BYTE Red, BYTE Green, BYTE Blue, bool SetAsClassBrush = false);

	// Preset window icon
	void PresetIcon(HINSTANCE hInstance, ULONG ResourceID);

	// Preset window small icon
	void PresetIconSm(HINSTANCE hInstance, ULONG ResourceID);

	// Preset HMENU
	void PresetMenu(HINSTANCE hInstance, WORD ResourceID);

	// Preset tool bar
	void PresetToolBar(UINT nButtons, UINT IconWidth, UINT IconHeight);

	// Preset tool bar icon
	// Create an Image List with PresetToolBar() before calling this function
	void PresetAddToolBarIcon(HINSTANCE hInstance, ULONG ResourceID);

	// Preset status bar part count
	void PresetStatusBar(INT nParts);

	// Preset creation options that can override Style and Extended Style
	void PresetOptions(WindowOptions e_Options);

	// Create parent window
	void Create(int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

	// Create child window
	HWND CreateChild(int x, int y, int Width, int Height, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

	// Add child window
	bool AddChildWindow(HWND hWndChild, bool b_Borderless);

	// Resize to window
	bool ResizeToWindow(HWND hWndChild, bool b_Center = true);

	// Get child window count
	std::size_t GetChildWindowCount(void) const { return v_ChildWindows.size(); }

	// Get child window
	Standard_Window* GetChildWindow(UINT Index) { return v_ChildWindows[Index].get(); }

	// Create tooltip
	HWND CreateTooltip(HWND hWndParent, ULONG ResourceID, StringW Tooltip);

	// Set accelerator table
	void SetAcceleratorTable(HINSTANCE hInstance, ULONG ResourceID)
	{
		h_AccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(ResourceID));

		if (!h_AccelTable) { Message(L"An error occurred when trying to load the window accelerator table."); }
	}

	// Get accelerator table
	HACCEL GetAcceleratorTable(void) const { return h_AccelTable; }

	// Get window handle
	HWND GetHandle(void) const { return hWnd; }

	// Get instance handle
	HINSTANCE GetInstance(void) const { return h_Instance; }

	// Get menu handle
	HMENU GetMenu(void) const { return h_Menu; }

	// Get window color
	COLORREF GetColor(void) const { return m_Color; }

	// Get window DPI scale factor
	FLOAT GetScaleFactor(void) const { return static_cast<FLOAT>(m_WindowDPI) / USER_DEFAULT_SCREEN_DPI; }

	// Get window DPI scale factor by percentage
	UINT GetScaleFactorByPercentage(void) const { return std::to_underlying(m_ScaleFactor); }

	// Get window color brush
	HBRUSH GetBrush(void) const { return h_Brush; }

	// Get class brush
	HBRUSH GetClassBrush(void) const { return m_Class.hbrBackground; }

	// Get client rect width
	INT GetWidth(void) const { return m_Width; }

	// Get client rect height
	INT GetHeight(void) const { return m_Height; }

	// Get dropped files
	StrVecW GetDroppedFiles(void) const { return DroppedFiles; }

	// Empty the dropped file list
	void EmptyDroppedFiles(void) { DroppedFiles.clear(); }

	// Status bar message
	void Status(int iPart, const String _Message, ...);

	// Status bar message
	void Status(int iPart, const StringW _Message, ...);

	// Status bar message
	void StatusPercent(int iPart, UINT iIndex, UINT iTotal) { Status(iPart, L"%0.0f%%", (((double)iIndex / (double)iTotal) * 100)); }

	// Windows Process Messages
	void MsgActivate(WPARAM wParam, LPARAM lParam);
	void MsgSetFocus(WPARAM wParam, LPARAM lParam);
	void MsgKillFocus(WPARAM wParam, LPARAM lParam);
	void MsgPositionChanged(WPARAM wParam, LPARAM lParam);
	void MsgInputDeviceChange(WPARAM wParam, LPARAM lParam);
	void MsgInput(WPARAM wParam, LPARAM lParam);
	void MsgMouseWheel(WPARAM wParam, LPARAM lParam);
	void MsgMouseHWheel(WPARAM wParam, LPARAM lParam);
	void MsgDropFiles(WPARAM wParam, LPARAM lParam);
	void MsgDpiChanged(WPARAM wParam, LPARAM lParam);


};