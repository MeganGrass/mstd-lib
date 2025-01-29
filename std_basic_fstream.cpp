/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*
*/


#include "std_basic_fstream.h"


/*
	Get the file stream as an unsigned char vector
*/
[[nodiscard]] std::vector<std::uint8_t> Standard_Basic_FStream::buffer(void) try
{
	std::vector<std::uint8_t> _Buffer((size_t)(size(File())));

	read(File(), 0, _Buffer.data(), _Buffer.size());

	return _Buffer;
}
catch (...) { Exception(std::current_exception()); return std::vector<std::uint8_t>(); }


/*
	Open File Stream
*/
std::fstream Standard_Basic_FStream::open(std::filesystem::path _Filename, FileAccessMode e_Mode, bool b_Binary, bool b_Truncate) try
{
	// Error
	if (_Filename.empty()) { return std::fstream(); }

	// Path
	_Filename = CleanPath(_Filename);

	// Flag
	bool b_Exists = Exists(_Filename);
	bool b_NoCreate = (std::to_underlying(e_Mode) & NO_CREATE);
	bool b_NoReplace = (std::to_underlying(e_Mode) & NO_REPLACE);

	// Don't replace existing file
	if (b_NoReplace && b_Exists) { return std::fstream(); }

	// Don't create new file
	if (b_NoCreate && !b_Exists) { return std::fstream(); }

	// Mode
	std::ios_base::openmode openMode = b_Binary ? std::ios::binary : 0;
	switch (std::to_underlying(e_Mode) & (READ | WRITE | APPEND | READ_EX | WRITE_EX | APPEND_EX))
	{

	case READ:
		if (!b_Exists) { return std::fstream(); }
		openMode |= std::ios::in;
		break;

	case WRITE:
		if (!b_Exists) { CreateDirectory(_Filename); }
		openMode |= std::ios::out;
		if (b_Truncate) { openMode |= std::ios::trunc; }
		break;

	case APPEND:
		if (!b_Exists) { CreateDirectory(_Filename); }
		openMode |= std::ios::out;
		openMode |= std::ios::app;
		break;

	case READ_EX:
		if (!b_Exists) { return std::fstream(); }
		openMode |= std::ios::in;
		openMode |= std::ios::out;
		break;

	case WRITE_EX:
		if (!b_Exists) { CreateDirectory(_Filename); }
		openMode |= std::ios::in;
		openMode |= std::ios::out;
		openMode |= std::ios::trunc;
		break;

	case APPEND_EX:
		if (!b_Exists) { CreateDirectory(_Filename); }
		openMode |= std::ios::in;
		openMode |= std::ios::out;
		openMode |= std::ios::app;
		break;

	default:
		return std::fstream();

	}

	std::fstream _File{ _Filename, openMode };

	if (!_File.is_open()) { return std::fstream(); }

	return _File;
}
catch (...) { Exception(std::current_exception()); return std::fstream(); }


/*
	Open File Stream
*/
bool Standard_Basic_FStream::Open(std::filesystem::path _Filename, FileAccessMode e_Mode, bool b_Binary, bool b_Truncate) try
{
	SetPath(CleanPath(_Filename));

	m_Mode = e_Mode;

	m_Binary = b_Binary;

	m_Truncate = b_Truncate;

	m_File = std::make_unique<std::fstream>(open(Path(), e_Mode, b_Binary, b_Truncate));

	return File().is_open();
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Reopen File Stream
*/
bool Standard_Basic_FStream::Reopen(FileAccessMode e_Mode, bool b_Binary, bool b_Truncate) try
{
	if (!validPath()) { return false; }

	if (validFile()) { File().close(); }
	m_File.reset();

	m_Mode = e_Mode;

	m_Binary = b_Binary;

	m_Truncate = b_Truncate;

	m_File = std::make_unique<std::fstream>(open(Path(), m_Mode, m_Binary, m_Truncate));

	return File().is_open();
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Read
*/
std::uintmax_t Standard_Basic_FStream::read(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif

	_File.seekg(_Ptr, std::ios_base::beg);

	_File.read(reinterpret_cast<char*>(_Data), _ElementSize);

#if FILEREAD_SYNC
	_File.sync();
#endif

	return _File.tellg();
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Write
*/
std::uintmax_t Standard_Basic_FStream::write(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif

	_File.seekp(_Ptr, std::ios_base::beg);

	_File.write(reinterpret_cast<char*>(_Data), _ElementSize);

#if FILEWRITE_FLUSH
	_File.flush();
#endif 

	return _File.tellp();
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Read Next
*/
void Standard_Basic_FStream::readNext(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) try
{
	_File.seekg(_Ptr, std::ios_base::beg);

	_File.read(reinterpret_cast<char*>(_Data), _ElementSize);

#if FILEREAD_SYNC
	_File.sync();
#endif
}
catch (...) { Exception(std::current_exception()); }


/*
	Write Next
*/
void Standard_Basic_FStream::writeNext(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) try
{
	_File.seekp(_Ptr, std::ios_base::beg);

	_File.write(reinterpret_cast<char*>(_Data), _ElementSize);

#if FILEWRITE_FLUSH
	_File.flush();
#endif 
}
catch (...) { Exception(std::current_exception()); }


/*
	Read String
*/
std::uintmax_t Standard_Basic_FStream::readStr(std::fstream& _File, std::uintmax_t _Ptr, String& _OutStr, UCharVec _DelimiterList) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	std::uintmax_t _FileSize = size(_File);

	// Find First Delimiter
	bool _Break = false;
	std::uint8_t _Peek = 0;
	std::uint8_t c_Delimiter = '\r';
	std::uintmax_t _BufferSize = 0;
	std::uintmax_t p_Ptr = _Ptr;
	do {

		readNext(_File, p_Ptr, &_Peek, 1);

		for (auto& _List : _DelimiterList)
		{
			if (_Peek == _List)
			{
				c_Delimiter = _List;
				_Break = true;
				break;
			}
		}

		if (_Break) { break; }

		_BufferSize++;

		p_Ptr += 1;

	} while ((p_Ptr < _FileSize) && (!_File.eof()));

	// Read
	std::vector<char> _Buffer((size_t)(_BufferSize + sizeof(char)));
	readNext(_File, _Ptr, _Buffer.data(), _BufferSize);

	_OutStr.erase();
	_OutStr = _Buffer.data();

	return _File.tellg();
}
catch (...) { Exception(std::current_exception()); return 0; }

std::uintmax_t Standard_Basic_FStream::readStr(std::fstream& _File, std::uintmax_t _Ptr, StringW& _OutStr, bool b_SwapBytes, std::vector<std::wint_t> _DelimiterList) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	std::uintmax_t _FileSize = size(_File);

	// Find First Delimiter
	bool _Break = false;
	std::wint_t _Peek = 0;
	std::wint_t c_Delimiter = L'\r';
	std::uintmax_t _BufferSize = 0;
	std::uintmax_t p_Ptr = _Ptr;
	do {

		readNext(_File, p_Ptr, &_Peek, sizeof(std::wint_t));

		if (b_SwapBytes) _Peek = std::byteswap<std::wint_t>(_Peek);

		for (auto& _List : _DelimiterList)
		{
			if (_Peek == _List)
			{
				c_Delimiter = _List;
				_Break = true;
				break;
			}
		}

		if (_Break) { break; }

		_BufferSize += sizeof(std::wint_t);

		p_Ptr += sizeof(std::wint_t);

	} while ((p_Ptr < _FileSize) && (!_File.eof()));

	// Read
	std::vector<wchar_t> _Buffer((size_t)(_BufferSize + sizeof(wchar_t)));
	readNext(_File, _Ptr, _Buffer.data(), _BufferSize);

	if (b_SwapBytes)
	{
		for (std::uintmax_t i = 0; i < _BufferSize; i++)
		{
			_Buffer[(size_t)i] = std::byteswap<wchar_t>(_Buffer[(size_t)i]);
		}
	}

	_OutStr.erase();
	_OutStr = _Buffer.data();

	return _File.tellg();
}
catch (...) { Exception(std::current_exception()); return 0; }

std::uintmax_t Standard_Basic_FStream::readStr(std::fstream& _File, std::uintmax_t _Ptr, String32& _OutStr, bool b_SwapBytes, std::vector<char32_t> _DelimiterList) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	std::uintmax_t _FileSize = size(_File);

	// Find First Delimiter
	bool _Break = false;
	char32_t _Peek = 0;
	char32_t c_Delimiter = U'\r';
	std::uintmax_t _BufferSize = 0;
	std::uintmax_t p_Ptr = _Ptr;
	do {

		readNext(_File, p_Ptr, &_Peek, sizeof(char32_t));

		if (b_SwapBytes) _Peek = std::byteswap<char32_t>(_Peek);

		for (auto& _List : _DelimiterList)
		{
			if (_Peek == _List)
			{
				c_Delimiter = _List;
				_Break = true;
				break;
			}
		}

		if (_Break) { break; }

		_BufferSize += sizeof(char32_t);

		p_Ptr += sizeof(char32_t);

	} while ((p_Ptr < _FileSize) && (!_File.eof()));

	// Read
	std::vector<char32_t> _Buffer((size_t)(_BufferSize + sizeof(char32_t)));
	readNext(_File, _Ptr, _Buffer.data(), _BufferSize);

	if (b_SwapBytes)
	{
		for (std::uintmax_t i = 0; i < _BufferSize; i++)
		{
			_Buffer[(size_t)i] = std::byteswap<char32_t>(_Buffer[(size_t)i]);
		}
	}

	_OutStr.erase();
	_OutStr = _Buffer.data();

	return _File.tellg();
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Write String
*/
std::uintmax_t Standard_Basic_FStream::writeStr(std::fstream& _File, std::uintmax_t _Ptr, String _String, bool b_NullTerminator) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	_File.seekp(_Ptr, std::ios_base::beg);

	_File << _String;

#if FILEWRITE_FLUSH
	_File.flush();
#endif

	if (b_NullTerminator) { _File << std::ends; }

	return _File.tellp();
}
catch (...) { Exception(std::current_exception()); return 0; }

std::uintmax_t Standard_Basic_FStream::writeStr(std::fstream& _File, std::uintmax_t _Ptr, StringW _String, bool b_NullTerminator) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	_File.seekp(_Ptr, std::ios_base::beg);

	write(_File, _Ptr, _String.data(), _String.size() * sizeof(std::wint_t));

	if (b_NullTerminator) { for (auto n = 0; n < 4; n++) _File << std::ends; }

	return _File.tellp();
}
catch (...) { Exception(std::current_exception()); return 0; }

std::uintmax_t Standard_Basic_FStream::writeStr(std::fstream& _File, std::uintmax_t _Ptr, String32 _String, bool b_NullTerminator) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif 

	_File.seekp(_Ptr, std::ios_base::beg);

	write(_File, _Ptr, _String.data(), _String.size() * sizeof(char32_t));

	if (b_NullTerminator) { for (auto n = 0; n < 8; n++) _File << std::ends; }

	return _File.tellp();
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Find
*/
std::uintmax_t Standard_Basic_FStream::find(void* _Data, std::uintmax_t _ElementSize, std::uintmax_t _PtrStart, std::uintmax_t _PtrEnd) try
{
	if ((!validFile()) || (!_ElementSize)) { return -1; }

	std::uintmax_t _FileSize = FileSize(Path());

	if (_PtrEnd == -1) { _PtrEnd = _FileSize; }

	if (_PtrStart >= _PtrEnd) { return -1; }

	std::vector<std::uint8_t> _Buffer((size_t)_ElementSize);

	while (_PtrStart < _PtrEnd)
	{
		readNext(File(), _PtrStart, _Buffer.data(), _ElementSize);

		if (std::memcmp(_Buffer.data(), _Data, (size_t)_ElementSize) == 0)
		{
			return _PtrStart;
		}

		_PtrStart++;
	}

	return -1;
}
catch (...) { Exception(std::current_exception()); return -1; }


/*
	Create
*/
bool Standard_Basic_FStream::Create(std::filesystem::path _Filename, void* _Source, std::uintmax_t _ElementSize, bool b_OverwriteExisting)
{
	FileAccessMode e_Mode { FileAccessMode::Write };

	if (!b_OverwriteExisting) { e_Mode = FileAccessMode::Write | FileAccessMode::No_Replace; }

	StdFile _File { _Filename, e_Mode, true, true };

	if (!_File.IsOpen()) { return false; }

	write(_File.File(), 0, _Source, _ElementSize);

	return true;
}


/*
	File Size
*/
std::uintmax_t Standard_Basic_FStream::size(std::fstream& _File) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif

	switch (std::to_underlying(m_Mode) & (READ | WRITE | APPEND | READ_EX | WRITE_EX | APPEND_EX))
	{

	case READ:
	case READ_EX:
	case WRITE_EX:
	case APPEND_EX:
		_File.seekg(0, std::ios_base::end);
		return _File.tellg();

	case WRITE:
	case APPEND:
		_File.seekp(0, std::ios_base::end);
		return _File.tellp();

	}

	return 0;
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	File Position
*/
std::uintmax_t Standard_Basic_FStream::tell(std::fstream& _File) try
{
#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif

	switch (std::to_underlying(m_Mode) & (READ | WRITE | APPEND | READ_EX | WRITE_EX | APPEND_EX))
	{

	case READ:
	case READ_EX:
	case WRITE_EX:
	case APPEND_EX:
		return _File.tellg();

	case WRITE:
	case APPEND:
		return _File.tellp();

	}

	return 0;
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Align File Size
*/
bool Standard_Basic_FStream::ResizeAlign(std::uintmax_t _BlockSize)
{
	std::uintmax_t _Size = FileSize(Path());

	std::uintmax_t _Remainder = _Size % _BlockSize;

	if (_Remainder == 0) { return true; }

	return ResizeFile(Path(), _Size + (_BlockSize - _Remainder));
}


/*
	Align the file stream's position to a specified block size in bytes
*/
std::uintmax_t Standard_Basic_FStream::PosAlign(std::uintmax_t& _Ptr, std::uintmax_t BlockSize)
{
	if (_Ptr % BlockSize)
	{
		_Ptr += BlockSize - (_Ptr % BlockSize);
	}

#if FILEOPEN_CHECK
	if (!_File.is_open()) { return 0; }
#endif

	switch (std::to_underlying(m_Mode) & (READ | WRITE | APPEND | READ_EX | WRITE_EX | APPEND_EX))
	{

	case READ:
	case READ_EX:
	case WRITE_EX:
	case APPEND_EX:
		File().seekg(_Ptr, std::ios_base::beg);
		return File().tellg();

	case WRITE:
	case APPEND:
		File().seekp(_Ptr, std::ios_base::beg);
		return File().tellp();

	}

	return _Ptr;
}


/*
	Get CRC32
*/
std::uint32_t Standard_Basic_FStream::CRC32(std::uintmax_t _Ptr, std::uintmax_t _ElementSize)
{
	if ((!validFile()) || (!_ElementSize)) { return 0; }

	std::vector<std::uint8_t> _Buffer((size_t)_ElementSize);

	read(File(), 0, _Buffer.data(), _ElementSize);

	std::uint32_t _CRC32 = GetCRC32(_Buffer.data(), _ElementSize);

	return _CRC32;
}