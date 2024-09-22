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


// Language Support Library
#include <version>


// Data Types and Defines
#include "std_data_types.h"
#include "std_defines.h"
#include "std_cstyle.h"


// Exception
#include <stdexcept>
#include <format>
#include <source_location>
#include <stacktrace>
#include <iostream>


// Windows
#ifdef _WINDOWS
#include <SDKDDKVer.h>
#include <Windows.h>
#include <Windowsx.h>
#define DEBUGGING_SESSION	IsDebuggerPresent()
#endif


/*
*	https://en.cppreference.com/w/cpp/header/exception
*/
class Standard_Exception {
private:


	/*
		Move
	*/
	Standard_Exception(Standard_Exception&&) = delete;
	Standard_Exception& operator = (Standard_Exception&&) = delete;


	/*
		Copy
	*/
	Standard_Exception(const Standard_Exception&) = delete;
	Standard_Exception& operator = (const Standard_Exception&) = delete;


	/*
		Console Log
	*/
	virtual void ExceptionTerminate(std::exception& _Exception, bool bTerminate = true, const std::source_location Location = std::source_location::current());


protected:


	/*
		Format String
	*/
	template<typename... Args>
	std::string FormatString(const std::format_string<Args...> _Format, Args&&... _Args)
	{
		return std::vformat(_Format.get(), std::make_format_args(_Args...));
	}


	/*
		All-in-One Exception Handler
	*/
	virtual void Exception(std::exception_ptr pException, bool bTerminate = true, const std::source_location Location = std::source_location::current());


public:


	/*
		Exception Pointer
	*/
	static std::exception_ptr p_Exception;


	/*
		De/Construction
	*/
	explicit constexpr Standard_Exception(void) noexcept = default;
	virtual ~Standard_Exception(void) noexcept = default;


};