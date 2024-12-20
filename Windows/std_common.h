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

	using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

	// Window
	HINSTANCE hInstance;					// Module Handle
	HWND hWndOwner;							// Owner Window Handle

	// Timer
	HANDLE h_Timer;							// Timer Handle
	LARGE_INTEGER m_DueTime;				// Due Time
	LONGLONG m_TimerFPS;					// Timer Frames Per Second
	DWORD m_TimerMilliFPS;					// Timer Frames Per Second in milliseconds

	// Chrono Timer
	LONGLONG m_ChronoFPS;					// Chrono Frames Per Second
	TimePoint t_Start;						// Chrono Timer Begin Time
	TimePoint t_Finish;						// Chrono Timer End Time

	// Performance
	LONGLONG m_PerformanceFrequency;		// Performance Frequency
	LONGLONG m_PerformanceCounter;			// Performance Counter

	// Convert the chrono frames per second to a double
	[[nodiscard]] double ChronoFPS() const { return 500.0f / static_cast<double>(m_ChronoFPS); }

	static HRESULT CALLBACK MessageModalCallbackProc(HWND hwnd, UINT uNotification, WPARAM wParam, LPARAM lParam, LONG_PTR dwRefData);
	
protected:


	/*
		Set the module handle
	*/
	void SetCommonInstance(HINSTANCE _hInstance) { hInstance = _hInstance; }


	/*
		Set the owner window handle
	*/
	void SetCommonOwner(HWND _hWndOwner) { hWndOwner = _hWndOwner; }


public:

	explicit Standard_Windows_Common(void) :
		hInstance(GetModuleHandleW(GetModuleStr().wstring().c_str())),
		hWndOwner(nullptr),
		h_Timer(nullptr),
		m_DueTime{},
		m_TimerFPS(60),
		m_TimerMilliFPS(1666666666),
		m_ChronoFPS(60),
		t_Start(std::chrono::steady_clock::now()),
		t_Finish(std::chrono::steady_clock::now()),
		m_PerformanceFrequency(0),
		m_PerformanceCounter(0)
	{
		if (FAILED(CoInitializeEx(0, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) { GetErrorMessage(); }
	}

	virtual ~Standard_Windows_Common(void)
	{
		if (h_Timer) { CloseHandle(h_Timer); }
		CoUninitialize();
	}


	/*
		Inheritance
	*/
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


	/*
		Get instance handle
	*/
	[[nodiscard]] virtual HINSTANCE GetInstance(void) const { return hInstance; }


	/*
		Get window handle
	*/
	[[nodiscard]] virtual HWND GetWindow(void) const { return hWndOwner; }


	/*
		Message from GetLastError() function
	*/
	void GetErrorMessage(bool b_ExitProcess = true, const std::source_location Location = std::source_location::current());


	/*
		Get the executable directory and filename
	*/
	[[nodiscard]] std::filesystem::path GetModuleStr(void);


	/*
		Get the executable directory
	*/
	[[nodiscard]] std::filesystem::path GetModuleDir(void);


	/*
		Get the %USERPROFILE% directory
	*/
	[[nodiscard]] std::filesystem::path GetUserDir(void);


	/*
		Get the %USERPROFILE% Documents directory
	*/
	[[nodiscard]] std::filesystem::path GetUserDocumentsDir(void);


	/*
		Get the %USERPROFILE% Saved Games directory
	*/
	[[nodiscard]] std::filesystem::path GetUserSavedGamesDir(void);


	/*
		Open File Dialog
	*/
	[[nodiscard]] std::optional<std::filesystem::path> GetOpenFilename(StrVecW _Description = { L"All Files" }, StrVecW _Filter = { L"*.*" });


	/*
		Save File Dialog
	*/
	[[nodiscard]] std::optional<std::filesystem::path> GetSaveFilename(StrVecW _Description = { L"All Files" }, StrVecW _Filter = { L"*.*" });


	/*
		Get Folder Dialog
	*/
	[[nodiscard]] std::optional<std::filesystem::path> GetFileDirectory(void) const;


	/*
		Message Box Question
	*/
	[[nodiscard]] bool Question(const std::wstring _Question, ...) const;


	/*
		Message Box
	*/
	virtual void Message(const std::string _Format, ...) override;


	/*
		Message Box
	*/
	virtual void Message(const std::wstring _Format, ...) override;


	/*
		Message Modal
		 - hyperlinks are supported in Content:
			<a href=\"https://example.com\">https://example.com</a>
	*/
	void MessageModal(const std::wstring& Title, const std::wstring& MainInstruction, const std::wstring _Content, ...) const;


	/*
		Performance measurement begin
	*/
	void PerformanceStart(void)
	{
		LARGE_INTEGER StartFrequency{};
		QueryPerformanceFrequency(&StartFrequency);
		m_PerformanceFrequency = (StartFrequency.QuadPart / 1000);
		QueryPerformanceCounter(&StartFrequency);
		m_PerformanceCounter = StartFrequency.QuadPart;

	}


	/*
		Performance measurement end
	*/
	[[nodiscard]] double PerformanceStop(void) const
	{
		LARGE_INTEGER EndCounter{};
		QueryPerformanceCounter(&EndCounter);
		return static_cast<double>(EndCounter.QuadPart - m_PerformanceCounter) / static_cast<double>(m_PerformanceFrequency);
	}


	/*
		Initialize a generic fps timer for use with CreateWaitableTimerEx()
	*/
	void SetTimer(LONGLONG FPS = 60)
	{
		m_TimerFPS = FPS;
		double Frequency = (1000.0f / static_cast<double>(m_TimerFPS)) * 10000.0f;
		LONGLONG TimerLimit = static_cast<LONGLONG>(Frequency);
		m_TimerMilliFPS = static_cast<DWORD>(TimerLimit);
		m_DueTime.QuadPart = -(TimerLimit);
		h_Timer = CreateWaitableTimerExW(0, 0, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
	}


	/*
		Wait for the generic fps timer to expire with WaitForSingleObject()
	*/
	void SleepTimer(void) const
	{
		SetWaitableTimerEx(h_Timer, &m_DueTime, 0, 0, 0, 0, 0);
		WaitForSingleObject(h_Timer, m_TimerMilliFPS);
	}


	/*
		Set chrono timer fps
	*/
	void SetChronoFPS(LONGLONG FPS = 60) { m_ChronoFPS = FPS; }


	/*
		Chrono timer start
	*/
	void ChronoTimerBegin(void)
	{
		t_Start = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> WorkTime = t_Start - t_Finish;
		if (WorkTime.count() < ChronoFPS())
		{
			std::chrono::duration<double, std::milli> Delta(ChronoFPS() - WorkTime.count());
			std::this_thread::sleep_until(t_Start + Delta);
		}
	}


	/*
		Chrono timer finish
	*/
	void ChronoTimerEnd(void) { t_Finish = std::chrono::steady_clock::now(); }


};