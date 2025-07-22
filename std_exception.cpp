/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#include "std_exception.h"


std::exception_ptr Standard_Exception::p_Exception = nullptr;


void Standard_Exception::ExceptionTerminate(std::exception& _Exception, bool bTerminate, const std::source_location Location)
{
	std::string strException = FormatString("\r\nException: {}\r\nFile: {}\r\nFunction: \'{}\'\r\n\r\nCall Stack:\r\n{}\r\n\r\n", _Exception.what(), Location.file_name(), Location.function_name(), std::stacktrace::current());

#ifdef _WINDOWS
	OutputDebugStringA(strException.c_str());
#else
	std::cerr << strException;
#endif

	if (bTerminate) { std::terminate(); }
}

void Standard_Exception::Exception(std::exception_ptr pException, bool bTerminate, const std::source_location Location)
{
	try { if (pException) std::rethrow_exception(pException); }
	catch (const std::exception& Exception) { ExceptionTerminate(const_cast<std::exception&>(Exception), bTerminate, Location); }
	catch (...) {
		std::runtime_error Exception("undefined exception");
		ExceptionTerminate(Exception, bTerminate, Location);
	}
}