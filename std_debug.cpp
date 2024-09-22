/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*
*/


#include "std_debug.h"


#if AUTO_REDIRECT_STDCOUT
DebugStream _StreamOut { std::cout };
#endif

#if AUTO_REDIRECT_STDCERR
DebugStream _StreamErr { std::cerr };
#endif

#if AUTO_REDIRECT_STDCLOG
DebugStream _StreamLog { std::clog };
#endif

#if AUTO_REDIRECT_STDWOUT
DebugStream _StreamOutW { std::wcout };
#endif

#if AUTO_REDIRECT_STDWERR
DebugStream _StreamErrW { std::wcerr };
#endif

#if AUTO_REDIRECT_STDWLOG
DebugStream _StreamLogW { std::wclog };
#endif



void Standard_Debug_Output::Initialize(StdOutStream e_StreamTypes, std::filesystem::path _Filename) try
{

	// File Output
	bool b_FileOut = false;
	if ((std::to_underlying(e_StreamTypes) & STDOUT) ||
		(std::to_underlying(e_StreamTypes) & STDERR) ||
		(std::to_underlying(e_StreamTypes) & STDLOG))
	{
		if ((!_File.is_open()) && (!_Filename.empty()) && (_Filename != ""))
		{
			_Filename = CleanPath(_Filename);
			_Filename.replace_extension(L".log");
			_File = std::fstream{ _Filename, std::ios::out | std::ios::trunc };
			if (_File.is_open()) { b_FileOut = true; }
		}
		else { b_FileOut = true; }
	}

	if ((std::to_underlying(e_StreamTypes) & STDOUTW) ||
		(std::to_underlying(e_StreamTypes) & STDERRW) ||
		(std::to_underlying(e_StreamTypes) & STDLOGW))
	{
		if ((!_File.is_open()) && (!_Filename.empty()) && (_Filename != ""))
		{
			_Filename = CleanPath(_Filename);
			_Filename.replace_extension(L".w.log");
			_FileW = std::wfstream{ _Filename, std::ios::out | std::ios::trunc };
			if (_FileW.is_open()) { b_FileOut = true; }
		}
		else { b_FileOut = true; }
	}

	// std::cout
	if (std::to_underlying(e_StreamTypes) & STDOUT)
	{
#if AUTO_REDIRECT_STDCOUT
		if (b_FileOut) { _StreamOut.SetOutputFile(_File); }
#endif
	}

	// std::cerr
	if (std::to_underlying(e_StreamTypes) & STDERR)
	{
#if AUTO_REDIRECT_STDCERR
		if (b_FileOut) { _StreamErr.SetOutputFile(_File); }
#endif
	}

	// std::clog
	if (std::to_underlying(e_StreamTypes) & STDLOG)
	{
#if AUTO_REDIRECT_STDCLOG
		if (b_FileOut) { _StreamLog.SetOutputFile(_File); }
#endif
	}

	// std::wcout
	if (std::to_underlying(e_StreamTypes) & STDOUTW)
	{
#if AUTO_REDIRECT_STDWOUT
		if (b_FileOut) { _StreamOutW.SetOutputFile(_FileW); }
#endif
	}

	// std::wcerr
	if (std::to_underlying(e_StreamTypes) & STDERRW)
	{
#if AUTO_REDIRECT_STDWERR
		if (b_FileOut) { _StreamErrW.SetOutputFile(_FileW); }
#endif
	}

	// std::wclog
	if (std::to_underlying(e_StreamTypes) & STDLOGW)
	{
#if AUTO_REDIRECT_STDWLOG
		if (b_FileOut) { _StreamLogW.SetOutputFile(_FileW); }
#endif
	}

}
catch (...) { Exception(std::current_exception()); }