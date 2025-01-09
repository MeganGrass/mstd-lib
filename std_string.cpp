/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*		CleanString maybe needs a rewrite
* 
*		Fix formatting for wide strings to handle Unicode characters
*/


#include "std_string.h"

#include <sstream>

#include <algorithm>

#include <ranges>

#include <iomanip>


/*
	Common String Functionality
*/
std::unique_ptr<Standard_String> Str = std::make_unique<Standard_String>();


/*
	Format C-Style String
*/
std::string Standard_String::FormatCStyle(const std::string _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vsnprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(char));
	std::vector<char> String(_StrLen);
	std::vsnprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	return String.data();
}

std::wstring Standard_String::FormatCStyle(const std::wstring _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vswprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	return String.data();
}


/*
	Get hexadecimal string from integer value
*/
String Standard_String::GetHex(std::uintmax_t _Value)
{
	std::stringstream StringStream;
	StringStream << std::hex << _Value;
	return StringStream.str();
}


/*
	Empty String
*/
bool Standard_String::EmptyString(String _String)
{
	// Check for Whitespace
	if (std::all_of(_String.begin(), _String.end(), [](std::uint8_t x)
		{
			return std::isspace(x);
		})) {
		return true;
	}

	// Check for Empty
	return _String.empty();
}

bool Standard_String::EmptyString(StringW _String)
{
	// Check for Whitespace
	if (std::all_of(_String.begin(), _String.end(), [](std::wint_t x)
		{
			return std::iswspace(x);
		})) {
		return true;
	}

	// Check for Empty
	return _String.empty();
}


/*
	Empty String Vector
*/
bool Standard_String::EmptyStrVec(StrVec _StrVec)
{
	// Check for Whitespace
	if (std::all_of(_StrVec.begin(), _StrVec.end(), [](std::string x)
		{
			return x.empty();
		})) {
		return true;
	}

	// Check for Empty
	return _StrVec.empty();
}

bool Standard_String::EmptyStrVec(StrVecW _StrVec)
{
	// Check for Whitespace
	if (std::all_of(_StrVec.begin(), _StrVec.end(), [](std::wstring x)
		{
			return x.empty();
		})) {
		return true;
	}

	// Check for Empty
	return _StrVec.empty();
}


/*
	To Upper
*/
String Standard_String::ToUpper(String& _String)
{
	std::transform(_String.cbegin(), _String.cend(), _String.begin(), [](std::uint8_t c) { return std::toupper(c); });
	return _String;
}

StringW Standard_String::ToUpper(StringW& _String)
{
	std::transform(_String.cbegin(), _String.cend(), _String.begin(), [](std::wint_t c) { return std::towupper(c); });
	return _String;
}


/*
	To Lower
*/
String Standard_String::ToLower(String& _String)
{
	std::transform(_String.cbegin(), _String.cend(), _String.begin(), [](std::uint8_t c) { return std::tolower(c); });
	return _String;
}

StringW Standard_String::ToLower(StringW& _String)
{
	std::transform(_String.cbegin(), _String.cend(), _String.begin(), [](std::wint_t c) { return std::towlower(c); });
	return _String;
}


/*
	Trim String
*/
void Standard_String::TrimString(String& _String) try
{
	// Reverse Erase Whitespaces
	_String.erase(std::ranges::find_if(_String | std::views::reverse, [](std::uint8_t x) { return !std::isspace(x); }).base(), _String.end());

	// Forward Erase Whitespaces
	_String.erase(_String.begin(), std::ranges::find_if(_String, [](std::uint8_t x) { return !std::isspace(x); }));
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::TrimString(StringW& _String) try
{
	// Reverse Erase Whitespaces
	_String.erase(std::ranges::find_if(_String | std::views::reverse, [](std::wint_t x) { return !std::iswspace(x); }).base(), _String.end());

	// Forward Erase Whitespaces
	_String.erase(_String.begin(), std::ranges::find_if(_String, [](std::wint_t x) { return !std::iswspace(x); }));
}
catch (...) { Exception(std::current_exception()); }


/*
	Clean String
*/
void Standard_String::CleanString(String& _String, StrVec _CleanList) try
{
	for (auto& _List : _CleanList)
	{
		if (_String.find(_List) != String::npos)
		{
			_String.erase(_String.find(_List), _List.size());
			if (_String.size() != _List.size()) { CleanString(_String, _CleanList); }
		}
	}
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::CleanString(StringW& _String, StrVecW _CleanList) try
{
	for (auto& _List : _CleanList)
	{
		if (_String.find(_List) != StringW::npos)
		{
			_String.erase(_String.find(_List), _List.size());
			if (_String.size() != _List.size()) { CleanString(_String, _CleanList); }
		}
	}
}
catch (...) { Exception(std::current_exception()); }


/*
	Clean String Vector
*/
void Standard_String::CleanStrVec(StrVec& _StrVec, StrVec _CleanList) try
{
	// Error
	//if (EmptyStrVec(_CleanList)) { return false; }

	// Clean Strings
	for (auto& _Strings : _StrVec) { CleanString(_Strings, _CleanList); }

	// Erase Empty Strings
	std::erase_if(_StrVec, [](String x) { return x.empty(); });

	// Erase Whitespaces
	for (auto& _Strings : _StrVec)
	{
		_Strings.erase(std::remove_if(_Strings.begin(), _Strings.end(), [](std::uint8_t x)
			{
				return std::isspace(x);
			}), _Strings.end());
	}

	// Ensure Strings Don't Begin or End with Whitespace
	for (auto& _Strings : _StrVec) { TrimString(_Strings); }

	// Complete
	//return true;
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::CleanStrVec(StrVecW& _StrVec, StrVecW _CleanList) try
{
	// Error
	//if (EmptyStrVec(_CleanList)) { return false; }

	// Clean Strings
	for (auto& _Strings : _StrVec) { CleanString(_Strings, _CleanList); }

	// Erase Empty Strings
	std::erase_if(_StrVec, [](StringW x) { return x.empty(); });

	// Erase Whitespaces
	for (auto& _Strings : _StrVec)
	{
		_Strings.erase(std::remove_if(_Strings.begin(), _Strings.end(), [](std::wint_t x)
			{
				return std::iswspace(x);
			}), _Strings.end());
	}

	// Ensure Strings Don't Begin or End with Whitespace
	for (auto& _Strings : _StrVec) { TrimString(_Strings); }

	// Complete
	//return true;
}
catch (...) { Exception(std::current_exception()); }


/*
	Get String Vector
*/
StrVec Standard_String::GetStrVec(String _String) try
{
	// Output Op
	std::stringstream strStream(_String);

	// Output Vector
	StrVec ArgVec;

	// String Op
	while (strStream >> std::quoted(_String, { '"' }, { 0x00 })) { ArgVec.push_back(_String); }

	// Complete
	return ArgVec;
}
catch (...) { Exception(std::current_exception()); return StrVec(); }

StrVecW Standard_String::GetStrVec(StringW _String) try
{
	// Output Op
	std::wstringstream strStream(_String);

	// Output Vector
	StrVecW ArgVec;

	// String Op
	while (strStream >> std::quoted(_String, { '"' }, { 0x00 })) { ArgVec.push_back(_String); }

	// Complete
	return ArgVec;
}
catch (...) { Exception(std::current_exception()); return StrVecW(); }

StrVec32 Standard_String::GetStrVec(String32 _String) try
{
	// Output Op
	std::basic_stringstream<std::u32string::value_type> strStream(_String);

	// Output Vector
	StrVec32 ArgVec;

	// String Op
	while (strStream >> std::quoted(_String)) { ArgVec.push_back(_String); }

	// Complete
	return ArgVec;
}
catch (...) { Exception(std::current_exception()); return StrVec32(); }


/*
	Compare String Vector
*/
bool Standard_String::StrVecCompare(StrVec _StrVec0, StrVec _StrVec1) try
{
	// Error
	if (_StrVec0.size() != _StrVec1.size()) { return false; }

	// Compare
	for (std::size_t i = 0; i < _StrVec0.size(); i++)
	{
		if(_StrVec0[i].compare(_StrVec1[i]) != 0) { return false; }
	}

	// Complete
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }

bool Standard_String::StrVecCompare(StrVecW _StrVec0, StrVecW _StrVec1) try
{
	// Error
	if (_StrVec0.size() != _StrVec1.size()) { return false; }

	// Compare
	for (std::size_t i = 0; i < _StrVec0.size(); i++)
	{
		if (_StrVec0[i].compare(_StrVec1[i]) != 0) { return false; }
	}

	// Complete
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	String Vector Assign
*/
void Standard_String::StrVecAssign(StrVec& _StrVec, std::size_t _Pos, String _String) try
{
	// Resize if Position is Out of Range
	if (_StrVec.empty() || (_Pos > (_StrVec.size() - 1))) { _StrVec.resize(_Pos + 1); }

	// Assign
	_StrVec.at(_Pos).assign(_String);
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::StrVecAssign(StrVecW& _StrVec, std::size_t _Pos, StringW _String) try
{
	// Resize if Position is Greater than Vector Size
	if (_StrVec.empty() || (_Pos > (_StrVec.size() - 1))) { _StrVec.resize(_Pos + 1); }

	// Assign
	_StrVec.at(_Pos).assign(_String);
}
catch (...) { Exception(std::current_exception()); }


/*
	String Vector Insert
*/
void Standard_String::StrVecInsert(StrVec& _StrVec, std::size_t _Pos, String _String) try
{
	// Resize if Position is Greater than Vector Size
	if (_StrVec.empty() || (_Pos > _StrVec.size())) { _StrVec.resize(_Pos); }

	// Insert
	_StrVec.insert(_StrVec.begin() + _Pos, _String);
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::StrVecInsert(StrVecW& _StrVec, std::size_t _Pos, StringW _String) try
{
	// Resize if Position is Greater than Vector Size
	if (_StrVec.empty() || (_Pos > _StrVec.size())) { _StrVec.resize(_Pos); }

	// Insert
	_StrVec.insert(_StrVec.begin() + _Pos, _String);
}
catch (...) { Exception(std::current_exception()); }


/*
	String Vector Insert Range
*/
void Standard_String::StrVecInsertRange(StrVec& _StrVec, std::size_t _Pos, StrVec _VecIn) try
{
	// Resize if Position is out of Range
	if (_StrVec.empty() && _VecIn.empty()) { _StrVec.resize(_Pos + 1); }
	else if (_StrVec.empty() || (_Pos > _StrVec.size())) { _StrVec.resize(_Pos); }

	// Insert Range
	_StrVec.insert_range(std::next(_StrVec.begin(), _Pos), _VecIn);
}
catch (...) { Exception(std::current_exception()); }

void Standard_String::StrVecInsertRange(StrVecW& _StrVec, std::size_t _Pos, StrVecW _VecIn) try
{
	// Resize if Position is out of Range
	if (_StrVec.empty() && _VecIn.empty()) { _StrVec.resize(_Pos + 1); }
	else if (_StrVec.empty() || (_Pos > _StrVec.size())) { _StrVec.resize(_Pos); }

	// Insert Range
	_StrVec.insert_range(std::next(_StrVec.begin(), _Pos), _VecIn);
}
catch (...) { Exception(std::current_exception()); }


/*
	Message Box Window
*/
void Standard_String::Message(const std::string _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vsnprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(char));
	std::vector<char> String(_StrLen);
	std::vsnprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

#ifdef _WINDOWS
	MessageBoxA(hWnd, String.data(), "Message", MB_OK);
#else
	std::cout << String.data() << std::endl;
#endif

}

void Standard_String::Message(const std::wstring _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vswprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

#ifdef _WINDOWS
	MessageBoxW(hWnd, String.data(), L"Message", MB_OK);
#else
	std::wcout << String.data() << std::endl;
#endif

}