/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
* 
*		Make Standard_Windows_System a singleton
*
*/


#pragma once

#include "std_common.h"

#include "../std_thread_pool.h"

#include <versionhelpers.h>


typedef class Standard_Windows_System StdWinSystem;
extern std::unique_ptr<StdWinSystem> WinSystem;


class Standard_Windows_System final :
	public Standard_Windows_Common,
	public Standard_Thread_Pool {
private:

	// Move
	Standard_Windows_System(Standard_Windows_System&&) = delete;
	Standard_Windows_System& operator = (Standard_Windows_System&&) = delete;

	// Copy
	Standard_Windows_System(const Standard_Windows_System&) = delete;
	Standard_Windows_System& operator = (const Standard_Windows_System&) = delete;

public:


	/*
		Construction
	*/
	explicit Standard_Windows_System(void)
	{
#ifdef _WINDOWS
		if (!IsWindows10OrGreater())
		{
			Message(L"Windows 10 or greater is required to run this application.");
			std::exit(EXIT_SUCCESS);
		}
#endif
	}


	/*
		Deconstruction
	*/
	virtual ~Standard_Windows_System(void) = default;


	/*
		Initialize common controls
		Must be called before creating the parent window and only once during the application's lifetime
	*/
	void InitCommonControls(void);


};