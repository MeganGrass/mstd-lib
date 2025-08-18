/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#pragma once

#include "std_exception.h"

#include "std_filesystem.h"

#include "std_string.h"

#include <thread>

#include <chrono>
using namespace std::chrono;

#include <shlobj_core.h>

#ifdef CreateDirectory
#undef CreateDirectory
#endif


class Standard_Windows_Common :
	protected Standard_FileSystem,
	protected Standard_String {
private:

	// Window
	HINSTANCE hInstance;					// Module Handle
	HWND hWndOwner;							// Owner Window Handle

	// Performance
	LONGLONG m_PerformanceFrequency;		// Performance Frequency
	LONGLONG m_PerformanceCounter;			// Performance Counter

	// Timer
	HANDLE h_Timer;							// Timer Handle
	LARGE_INTEGER m_DueTime;				// Due Time
	LONGLONG m_TimerFPS;					// Timer Frames Per Second
	DWORD m_TimerMilliFPS;					// Timer Frames Per Second in milliseconds

	// Chrono Timer
	double m_ChronoFPS;
	double m_TimeFrame;
	double m_TimeDelta;
	std::chrono::steady_clock::time_point m_LastFrameTime;
	std::chrono::steady_clock::time_point m_CurrentFrameTime;

	static HRESULT CALLBACK MessageModalCallbackProc(HWND hwnd, UINT uNotification, WPARAM wParam, LPARAM lParam, LONG_PTR dwRefData);
	
protected:

	// Set the module handle
	void SetCommonInstance(HINSTANCE _hInstance) { hInstance = _hInstance; }

	// Set the owner window handle
	void SetCommonOwner(HWND _hWndOwner) { hWndOwner = _hWndOwner; }


public:

	explicit Standard_Windows_Common(void) :
		hInstance(GetModuleHandleW(GetModuleStr().wstring().c_str())),
		hWndOwner(nullptr),
		m_PerformanceFrequency(0),
		m_PerformanceCounter(0),
		h_Timer(nullptr),
		m_DueTime{},
		m_TimerFPS(60),
		m_TimerMilliFPS(1666666666),
		m_ChronoFPS(60.0),
		m_TimeFrame(1000.0 / 60.0),
		m_TimeDelta(0.0)
	{
		if (FAILED(CoInitializeEx(0, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) { GetErrorMessage(); }
	}

	virtual ~Standard_Windows_Common(void)
	{
		if (h_Timer) { CloseHandle(h_Timer); }
		CoUninitialize();
	}

	using Standard_FileSystem::Exists;
	using Standard_FileSystem::CleanPath;
	using Standard_FileSystem::GetDirectory;
	using Standard_FileSystem::CreateDirectory;
	using Standard_FileSystem::GetCurrentWorkingDir;
	using Standard_FileSystem::SetCurrentWorkingDir;
	using Standard_FileSystem::GetTempDirectory;
	using Standard_FileSystem::GetFileName;
	using Standard_FileSystem::IsDirectory;
	using Standard_FileSystem::IsFile;
	using Standard_String::FormatCStyle;
	using Standard_String::GetStrVec;
	using Standard_String::GetCommandline;
	using Standard_String::GetCommandlineA;
	using Standard_String::GetCommandlineW;
	using Standard_String::ToUpper;
	using Standard_String::ToLower;

	// Get instance handle
	[[nodiscard]] virtual const HINSTANCE& GetInstance(void) const { return hInstance; }

	// Get window handle
	[[nodiscard]] virtual const HWND& GetWindow(void) const { return hWndOwner; }

	// Message from GetLastError() function
	void GetErrorMessage(bool b_ExitProcess = true, const std::source_location Location = std::source_location::current());

	// Get the executable directory and filename
	[[nodiscard]] const std::filesystem::path GetModuleStr(void);

	// Get the executable directory
	[[nodiscard]] const std::filesystem::path GetModuleDir(void);

	// Get the %USERPROFILE% directory
	[[nodiscard]] const std::filesystem::path GetUserDir(void);

	// Get the %USERPROFILE% Documents directory
	[[nodiscard]] const std::filesystem::path GetUserDocumentsDir(void);

	// Get the %USERPROFILE% Saved Games directory
	[[nodiscard]] const std::filesystem::path GetUserSavedGamesDir(void);

	// Get a full path list of Truetype Fonts in C:/Windows/Fonts
	[[nodiscard]] const std::vector<std::filesystem::path> GetFonts(void);

	// Open File Dialog
	[[nodiscard]] const std::optional<std::filesystem::path> GetOpenFilename(StrVecW _Description = { L"All Files" }, StrVecW _Filter = { L"*.*" });

	// Save File Dialog
	[[nodiscard]] const std::optional<std::filesystem::path> GetSaveFilename(StrVecW _Description = { L"All Files" }, StrVecW _Filter = { L"*.*" });

	// Get Folder Dialog
	[[nodiscard]] const std::optional<std::filesystem::path> GetFileDirectory(void) const;

	// Message Box Question
	[[nodiscard]] const bool Question(const std::wstring _Question, ...) const;

	// Message Box
	virtual void Message(const std::string _Format, ...) override;

	// Message Box
	virtual void Message(const std::wstring _Format, ...) override;

	/*
		Message Modal
		 - hyperlinks are supported in Content:
			<a href=\"https://example.com\">https://example.com</a>
	*/
	void MessageModal(const std::wstring& Title, const std::wstring& MainInstruction, const std::wstring _Content, ...) const;

	// Performance measurement begin
	void PerformanceStart(void)
	{
		LARGE_INTEGER StartFrequency{};
		QueryPerformanceFrequency(&StartFrequency);
		m_PerformanceFrequency = (StartFrequency.QuadPart / 1000);
		QueryPerformanceCounter(&StartFrequency);
		m_PerformanceCounter = StartFrequency.QuadPart;

	}

	// Performance measurement end
	[[nodiscard]] const double PerformanceStop(void) const
	{
		LARGE_INTEGER EndCounter{};
		QueryPerformanceCounter(&EndCounter);
		return static_cast<double>(EndCounter.QuadPart - m_PerformanceCounter) / static_cast<double>(m_PerformanceFrequency);
	}

	// Initialize a generic fps timer for use with CreateWaitableTimerEx()
	void SetTimer(LONGLONG FPS = 60)
	{
		m_TimerFPS = FPS;
		double Frequency = (1000.0f / static_cast<double>(m_TimerFPS)) * 10000.0f;
		LONGLONG TimerLimit = static_cast<LONGLONG>(Frequency);
		m_TimerMilliFPS = static_cast<DWORD>(TimerLimit);
		m_DueTime.QuadPart = -(TimerLimit);
		h_Timer = CreateWaitableTimerExW(0, 0, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
	}

	// Wait for the generic fps timer to expire with WaitForSingleObject()
	void SleepTimer(void) const
	{
		SetWaitableTimerEx(h_Timer, &m_DueTime, 0, 0, 0, 0, 0);
		WaitForSingleObject(h_Timer, m_TimerMilliFPS);
	}

	// Initialize the chrono timer
	void ChronoTimerInit(double TargetFPS)
	{
		m_ChronoFPS = TargetFPS;
		m_TimeFrame = 1000.0 / TargetFPS;
		m_LastFrameTime = std::chrono::high_resolution_clock::now();
	}

	// Update the chrono timer
	void ChronoTimerUpdate(void)
	{
		m_CurrentFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ElapsedTime = m_CurrentFrameTime - m_LastFrameTime;
		m_LastFrameTime = m_CurrentFrameTime;
		m_TimeDelta = ElapsedTime.count();
	}

	// Sleep the thread until the next frame is ready
	void ChronoTimerSleep(void) const
	{
		double SleepTime = m_TimeFrame - m_TimeDelta;
		if (SleepTime > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(SleepTime)));
		}
	}
};