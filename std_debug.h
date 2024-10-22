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

#include "std_filesystem.h"

#include <fstream>


/*
	If true (1), output from predefined text streams (std::cout, std::wcout, etc.) can be entirely suppressed
	To suppress all output from every predefined text stream, set DISABLE_ALL_STDOUT to 1, each AUTO_REDIRECT flag to 1 and include std_debug.cpp in the project
*/
#define DISABLE_ALL_STDOUT	0


/*
	Individual flags to automatically redirect output from predefined text streams to the DebugStream class
	std_debug.cpp must be included for these flags to have any effect
*/
#define AUTO_REDIRECT_STDCOUT	1	// std::cout
#define AUTO_REDIRECT_STDWOUT	1	// std::wcout
#define AUTO_REDIRECT_STDCERR	1	// std::cerr
#define AUTO_REDIRECT_STDWERR	1	// std::wcerr
#define AUTO_REDIRECT_STDCLOG	1	// std::clog
#define AUTO_REDIRECT_STDWLOG	1	// std::wclog


/*
	If REDIRECT_TO_ODS and IsDebuggerPresent() are both true (1), output from predefined text streams can be rerouted to OutputDebugString (Windows only)
	If DISABLE_ALL_STDOUT is true (1), this flag has no effect
*/
#define REDIRECT_TO_ODS		1


#ifdef _WINDOWS

#ifndef DEBUGGING_SESSION
#define DEBUGGING_SESSION	IsDebuggerPresent()
#endif

template<typename TChar, typename TTraits>
struct DebugOutputString;

template<>
struct DebugOutputString<char, std::char_traits<char>>
{
	template<typename Iterator>
	void operator()(Iterator begin, Iterator end) const
	{
		std::string _String(begin, end);
		OutputDebugStringA(_String.c_str());
	}
};

template<>
struct DebugOutputString<wchar_t, std::char_traits<wchar_t>>
{
	template<typename Iterator>
	void operator()(Iterator begin, Iterator end) const
	{
		std::wstring _String(begin, end);
		OutputDebugStringW(_String.c_str());
	}
};

#else
#define DEBUGGING_SESSION	0
#endif


/*
	Debug Stream

	Redirect output from a predefined text stream to a file, OutputDebugString (Windows only) or suppress it entirely
*/
template<typename TChar, typename TTraits = std::char_traits<TChar>>
class DebugStream : protected std::basic_streambuf<TChar, TTraits>
{
private:

	std::basic_ostream<TChar, TTraits>& m_Stream;
	[[maybe_unused]] std::basic_ostream<TChar, TTraits> m_FileStream = std::basic_ostream<TChar, TTraits>(nullptr);
	std::basic_streambuf<TChar, TTraits>* m_oldBuffer;

	bool b_DebuggerPresent;

public:

	DebugStream(std::basic_ostream<TChar, TTraits>& stream) :
		m_Stream(stream),
		m_oldBuffer(stream.rdbuf()),
		b_DebuggerPresent(REDIRECT_TO_ODS && DEBUGGING_SESSION)
	{
		stream.rdbuf(this);
	}

	virtual ~DebugStream()
	{
		m_Stream.rdbuf(m_oldBuffer);
	}

	void SetOutputFile(std::basic_ostream<TChar, TTraits>& fileStream)
	{
#if !DISABLE_ALL_STDOUT
		m_FileStream.rdbuf(fileStream.rdbuf());
#endif
	}

protected:

	// Append a character to the output sequence
	virtual typename TTraits::int_type overflow(typename TTraits::int_type c = TTraits::eof()) override
	{
#if !DISABLE_ALL_STDOUT
		int iRet = sync();
		if (!TTraits::eq_int_type(c, TTraits::eof()))
		{
			TChar _Char = TTraits::to_char_type(c);
#if _WINDOWS && REDIRECT_TO_ODS
			if (b_DebuggerPresent) { DebugOutputString<TChar, TTraits>()(&_Char, &_Char + 1); }
#endif
			m_FileStream << _Char;
			this->setp(this->pbase(), this->epptr());
		}
		return iRet == -1 ? TTraits::eof() : TTraits::not_eof(c);
#else
		return TTraits::eof();
#endif
	}

	// Synchronize the buffers with the associated character sequence
	virtual int sync(void) override try
	{
#if !DISABLE_ALL_STDOUT
		std::basic_string<TChar, TTraits> _String(this->pbase(), this->pptr());
		if (!_String.empty())
		{
#if _WINDOWS && REDIRECT_TO_ODS
			if (b_DebuggerPresent) { DebugOutputString<TChar, TTraits>()(this->pbase(), this->pptr()); }
#endif
			m_FileStream << _String;
			this->setp(this->pbase(), this->epptr());
		}
#endif
		return 0;
	}
	catch (...) { return -1; }

};


/*
	Standard Basic Output Stream Types
*/
enum class StdOutStream : int
{
	//	Func Parameter				// Description
	Out = 1 << 0,					// std::cout
	Err = 1 << 1,					// std::cerr
	Log = 1 << 2,					// std::clog
	OutW = 1 << 3,					// std::wcout
	ErrW = 1 << 4,					// std::wcerr
	LogW = 1 << 5,					// std::wclog
	All = Out | Err | Log,			// std::cout, std::cerr, std::clog
	AllWide = OutW | ErrW | LogW,	// std::wcout, std::wcerr, std::wclog
	AllStreams = All | AllWide,		// std::cout, std::cerr, std::clog, std::wcout, std::wcerr, std::wclog
};

static StdOutStream operator | (StdOutStream _Mode0, StdOutStream _Mode1)
{
	return static_cast<StdOutStream>(std::to_underlying(_Mode0) | std::to_underlying(_Mode1));
}


/*
	Standard Debug Output

	Simple helper class for SetOutputFile of DebugStream
*/
typedef class Standard_Debug_Output StdOut;
class Standard_Debug_Output :
	protected Standard_FileSystem {
private:

	// Standard Output Streams constants
	static constexpr int STDOUT = std::to_underlying(StdOutStream::Out);
	static constexpr int STDERR = std::to_underlying(StdOutStream::Err);
	static constexpr int STDLOG = std::to_underlying(StdOutStream::Log);
	static constexpr int STDOUTW = std::to_underlying(StdOutStream::OutW);
	static constexpr int STDERRW = std::to_underlying(StdOutStream::ErrW);
	static constexpr int STDLOGW = std::to_underlying(StdOutStream::LogW);

	// File Output Streams
	std::fstream _File;
	std::wfstream _FileW;

	// Initialize User Parameters
	void Initialize(StdOutStream e_StreamTypes, std::filesystem::path _Filename);

public:

	explicit Standard_Debug_Output(StdOutStream e_StreamTypes, std::filesystem::path _Filename)
	{
		Initialize(e_StreamTypes, _Filename);
	}

	explicit Standard_Debug_Output(void) noexcept = default;

	virtual ~Standard_Debug_Output(void) noexcept = default;

	// Initialize User Parameters
	void AddOutputStream(StdOutStream e_StreamTypes) { Initialize(e_StreamTypes, ""); }

};