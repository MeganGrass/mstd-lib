/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#pragma once


#include <cstdint>

#include <vector>

#include <string>


// Unsigned Char Vector
typedef std::vector<std::uint8_t> UCharVec;

// Char Vector
typedef std::vector<char> CharVec;

// Wide Char Vector
typedef std::vector<wchar_t> CharVecW;

// Standard String
typedef std::string String;

// Standard Wide String
typedef std::wstring StringW;

// Standard 32-bit String
typedef std::u32string String32;

// Standard String Vector
typedef std::vector<std::string> StrVec;

// Standard Wide String Vector
typedef std::vector<std::wstring> StrVecW;

// Standard 32-bit String Vector
typedef std::vector<std::u32string> StrVec32;

// Standard String List
typedef std::initializer_list<std::string> StrList;

// Standard Wide String List
typedef std::initializer_list<std::wstring> StrListW;

// Standard 32-bit String List
typedef std::initializer_list<std::u32string> StrList32;

#ifndef CHAR
typedef char				CHAR;
#endif

#ifndef WCHAR
typedef wchar_t				WCHAR;
#endif

#ifndef SCHAR
typedef std::int8_t			SCHAR;
#endif

#ifndef UCHAR
typedef std::uint8_t		UCHAR;
#endif

#ifndef SHORT
typedef std::int16_t		SHORT;
#endif

#ifndef USHORT
typedef std::uint16_t		USHORT;
#endif

#ifndef INT
typedef std::int32_t		INT;
#endif

#ifndef UINT
typedef std::uint32_t		UINT;
#endif

#ifndef LONG
typedef long int			LONG;
#endif

#ifndef ULONG
typedef unsigned long int	ULONG;
#endif

#ifndef LLONG
typedef std::int64_t		LLONG;
#endif

#ifndef ULLONG
typedef std::uint64_t		ULLONG;
#endif

#ifndef FLOAT
typedef float				FLOAT;
#endif

#ifndef DOUBLE
typedef double				DOUBLE;
#endif

#ifndef LDOUBLE
typedef long double			LDOUBLE;
#endif

#ifndef BYTE
typedef std::uint8_t		BYTE;
#endif

#ifndef WORD
typedef std::uint16_t		WORD;
#endif

#ifndef DWORD
typedef unsigned long int	DWORD;
#endif

#ifndef QWORD
typedef std::uint64_t		QWORD;
#endif

#ifndef BOOL
typedef std::int32_t		BOOL;
#endif