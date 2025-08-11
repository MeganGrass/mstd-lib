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


/*
*	https://en.cppreference.com/w/cpp/header/string
*/
class Standard_String :
	protected Standard_Exception {
private:

public:

#ifdef _WINDOWS
	HWND hWnd = nullptr;
#endif


	/*
	*	De/Construction
	*/
	explicit constexpr Standard_String(void) noexcept = default;
	explicit constexpr Standard_String(HWND hWnd) noexcept : hWnd(hWnd) {}
	virtual ~Standard_String(void) noexcept = default;


	/*
		Get wide string from string
	*/
	[[nodiscard]] std::wstring GetWide(const std::string _String) noexcept { return std::wstring(_String.begin(), _String.end()); }


	/*
		Format C-Style String
	*/
	[[nodiscard]] std::string FormatCStyle(const std::string _Format, ...);


	/*
		Format C-Style Wide String
	*/
	[[nodiscard]] std::wstring FormatCStyle(const std::wstring _Format, ...);


	/*
		Get hexadecimal string from integer value
	*/
	[[nodiscard]] String GetHex(std::uintmax_t _Value);


	/*
		Test a string for a single character or substring
	*/
	template<typename SubStrType>
	[[nodiscard]] bool TestString(const String _String, SubStrType _SubStrType) noexcept { return _String.contains(_SubStrType) ? true : false; }


	/*
		Test a string for a single character or substring
	*/
	template<typename SubStrType>
	[[nodiscard]] bool TestString(const StringW _String, SubStrType _SubStrType) noexcept { return _String.contains(_SubStrType) ? true : false; }


	/*
		Test a string vector for a single character or substring
	*/
	template<typename SubStrType>
	[[nodiscard]] bool TestStrVec(StrVec _StrVec, SubStrType _SubStrType) noexcept
	{
		for (auto& String : _StrVec) { if (String.contains(_SubStrType)) { return true; } }
		return false;
	}


	/*
		Test a string vector for a single character or substring
	*/
	template<typename SubStrType>
	[[nodiscard]] bool TestStrVec(StrVecW _StrVec, SubStrType _SubStrType) noexcept
	{
		for (auto& String : _StrVec) { if (String.contains(_SubStrType)) { return true; } }
		return false;
	}


	/*
		Return true if the string is empty or entirely filled with whitespace
	*/
	[[nodiscard]] bool EmptyString(String _String);


	/*
		Return true if the string is empty or entirely filled with whitespace
	*/
	[[nodiscard]] bool EmptyString(StringW _String);


	/*
		Return true if the string vector is empty or entirely filled with whitespace
	*/
	[[nodiscard]] bool EmptyStrVec(StrVec _StrVec);


	/*
		Return true if the string vector is empty or entirely filled with whitespace
	*/
	[[nodiscard]] bool EmptyStrVec(StrVecW _StrVec);


	/*
		Convert a string to uppercase
	*/
	String ToUpper(String& _String);


	/*
		Convert a string to uppercase
	*/
	StringW ToUpper(StringW& _String);


	/*
		Convert a string to lowercase
	*/
	String ToLower(String& _String);


	/*
		Convert a string to lowercase
	*/
	StringW ToLower(StringW& _String);


	/*
		Reformat a string to ensure that it doesn't begin or end with whitespace
	*/
	void TrimString(String& _String);


	/*
		Reformat a string to ensure that it doesn't begin or end with whitespace
	*/
	void TrimString(StringW& _String);


	/*
		Remove all elements in a string that match the clean list
	*/
	void CleanString(String& _String, StrVec _CleanList = { ",", "." });


	/*
		Remove all elements in a string that match the clean list
	*/
	void CleanString(StringW& _String, StrVecW _CleanList = { L",", L"." });


	/*
		Remove all elements in a string vector that match the clean list
	*/
	void CleanStrVec(StrVec& _StrVec, StrVec _CleanList = { ",", "." });


	/*
		Remove all elements in a string vector that match the clean list
	*/
	void CleanStrVec(StrVecW& _StrVec, StrVecW _CleanList = { L",", L"." });


	/*
		Split whitespace separated substrings into a string vector
	*/
	[[nodiscard]] StrVec GetStrVec(String _String);


	/*
		Split whitespace separated substrings into a string vector
	*/
	[[nodiscard]] StrVecW GetStrVec(StringW _String);


	/*
		Split whitespace separated substrings into a string vector
	*/
	[[nodiscard]] StrVec32 GetStrVec(String32 _String);


	/*
		Compare two string vectors and return true if they are equal
	*/
	[[nodiscard]] bool StrVecCompare(StrVec _StrVec0, StrVec _StrVec1);


	/*
		Compare two string vectors and return true if they are equal
	*/
	[[nodiscard]] bool StrVecCompare(StrVecW _StrVec0, StrVecW _StrVec1);


	/*
		Assign a string element into a specified position within a string vector
	*/
	void StrVecAssign(StrVec& _StrVec, std::size_t _Pos, String _String);


	/*
		Assign a string element into a specified position within a string vector
	*/
	void StrVecAssign(StrVecW& _StrVec, std::size_t _Pos, StringW _String);


	/*
		Insert a string element into a specified position within a string vector
	*/
	void StrVecInsert(StrVec& _StrVec, std::size_t _Pos, String _String);


	/*
		Insert a string element into a specified position within a string vector
	*/
	void StrVecInsert(StrVecW& _StrVec, std::size_t _Pos, StringW _String);


	/*
		Insert a string vector into a specified position within a string vector
	*/
	void StrVecInsertRange(StrVec& _StrVec, std::size_t _Pos, StrVec _VecIn);


	/*
		Insert a string vector into a specified position within a string vector
	*/
	void StrVecInsertRange(StrVecW& _StrVec, std::size_t _Pos, StrVecW _VecIn);


	/*
		Split whitespace separated substrings from the app command line into a string vector
	*/
	[[nodiscard]] StrVec GetCommandline(const char* lpCmdLine) { return GetStrVec(lpCmdLine); }


	/*
		Split whitespace separated substrings from the app command line into a string vector
	*/
	[[nodiscard]] StrVecW GetCommandline(const wchar_t* lpCmdLine) { return GetStrVec(lpCmdLine); }


	/*
		Split whitespace separated substrings from the app command line into a string vector
	*/
	[[nodiscard]] StrVec GetCommandline(int argc, const char* argv[]) { return StrVec(argv, argv + argc); }


	/*
		Split whitespace separated substrings from the app command line into a string vector
	*/
	[[nodiscard]] StrVecW GetCommandline(int argc, const wchar_t* argv[]) { return StrVecW(argv, argv + argc); }


	/*
		Split whitespace separated substrings from the app command line into a string vector (Windows only)
	*/
	[[nodiscard]] StrVec GetCommandlineA(void)
	{

#ifdef _WINDOWS
		return GetStrVec(GetCommandLineA());
#else
		return StrVec();
#endif

	}


	/*
		Split whitespace separated substrings from the app command line into a string vector (Windows only)
	*/
	[[nodiscard]] StrVecW GetCommandlineW(void)
	{

#ifdef _WINDOWS
		return GetStrVec(GetCommandLineW());
#else
		return StrVecW();
#endif

	}


	/*
		Display a message box popup dialog with a specified message (Windows only)
		Alternatively, print to std::cout when _WINDOWS is not defined
	*/
	virtual void Message(const std::string _Format, ...);


	/*
		Display a message box popup dialog with a specified message (Windows only)
		Alternatively, print to std::wcout when _WINDOWS is not defined
	*/
	virtual void Message(const std::wstring _Format, ...);


};