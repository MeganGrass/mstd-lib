/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: Create individual exception handlers for each exception type
*
*/


#include "std_exception.h"


/*
	Exception Pointer
*/
std::exception_ptr Standard_Exception::p_Exception = nullptr;


/*
	Console Log
*/
void Standard_Exception::ExceptionTerminate(std::exception& _Exception, bool bTerminate, const std::source_location Location)
{

	// Format
	std::string strException = FormatString("\r\nException: {}\r\nFile: {}\r\nFunction: \'{}\'\r\n\r\nCall Stack:\r\n{}\r\n\r\n", _Exception.what(), Location.file_name(), Location.function_name(), std::stacktrace::current());

	// Print
#ifdef _WINDOWS
	OutputDebugStringA(strException.c_str());
#else
	std::cerr << strException;
#endif

	// Terminate
	if (bTerminate) { std::terminate(); }
	//else { std::exit(EXIT_FAILURE); }

}


/*
	All-in-One Exception Handler
*/
void Standard_Exception::Exception(std::exception_ptr pException, bool bTerminate, const std::source_location Location)
{
	try { if (pException) std::rethrow_exception(pException); }
	catch (std::ios_base::failure& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::domain_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::invalid_argument& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::length_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::out_of_range& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::logic_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::overflow_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::underflow_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::range_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::system_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::runtime_error& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_alloc& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_cast& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_exception& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_typeid& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_variant_access& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::bad_weak_ptr& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
	catch (std::exception& Exception) { ExceptionTerminate(Exception, bTerminate, Location); }
}