/*
*
*	Megan Grass
*	January 01, 2024
* 
*/


#include "std_text.h"


void Standard_Text::GetTextFileBOM(std::uintmax_t _Ptr)
{
	// File Size
	std::uintmax_t _FileSize = File().Size();

	// BOM Buffer
	UCHAR _BomBytes[4]{};

	if (_FileSize >= 4)
	{
		// Read BOM
		File().Read(_Ptr, _BomBytes, 4);

		// UTF32 Little Endian
		if (_BomBytes[0] == 0xFF &&
			_BomBytes[1] == 0xFE &&
			_BomBytes[2] == 0x00 &&
			_BomBytes[3] == 0x00) { m_BOM = TextFileBOM::UTF32_LE; return; }

		// UTF32 Big Endian
		if (_BomBytes[0] == 0x00 &&
			_BomBytes[1] == 0x00 &&
			_BomBytes[2] == 0xFE &&
			_BomBytes[3] == 0xFF) { m_BOM = TextFileBOM::UTF32_BE; return; }

		// UTF-EBCDIC
		if (_BomBytes[0] == 0xDD &&
			_BomBytes[1] == 0x73 &&
			_BomBytes[2] == 0x66 &&
			_BomBytes[3] == 0x73) { m_BOM = TextFileBOM::UTF_EBCDIC; return; }

		// GB18030
		if (_BomBytes[0] == 0x84 &&
			_BomBytes[1] == 0x31 &&
			_BomBytes[2] == 0x95 &&
			_BomBytes[3] == 0x33) { m_BOM = TextFileBOM::GB_18030; return; }
	}

	if (_FileSize >= 3)
	{
		// Read BOM
		File().Read(_Ptr, _BomBytes, 3);

		// UTF8 with BOM
		if (_BomBytes[0] == 0xEF &&
			_BomBytes[1] == 0xBB &&
			_BomBytes[2] == 0xBF) { m_BOM = TextFileBOM::UTF8_BOM; return; }

		// UTF-7
		if (_BomBytes[0] == 0x2B &&
			_BomBytes[1] == 0x2F &&
			_BomBytes[2] == 0x76) { m_BOM = TextFileBOM::UTF7; return; }

		// UTF-1
		if (_BomBytes[0] == 0xF7 &&
			_BomBytes[1] == 0x64 &&
			_BomBytes[2] == 0x4C) { m_BOM = TextFileBOM::UTF1; return; }

		// SCSU
		if (_BomBytes[0] == 0x0E &&
			_BomBytes[1] == 0xFE &&
			_BomBytes[2] == 0xFF) { m_BOM = TextFileBOM::SCSU; return; }

		// BOCU-1
		if (_BomBytes[0] == 0xFB &&
			_BomBytes[1] == 0xEE &&
			_BomBytes[2] == 0x28) { m_BOM = TextFileBOM::BOCU_1; return; }
	}

	if (_FileSize >= 2)
	{
		// Read BOM
		File().Read(_Ptr, _BomBytes, 2);

		// UTF16 Little Endian
		if (_BomBytes[0] == 0xFF &&
			_BomBytes[1] == 0xFE) { m_BOM = TextFileBOM::UTF16_LE; return; }

		// UTF16 Big Endian
		if (_BomBytes[0] == 0xFE &&
			_BomBytes[1] == 0xFF) { m_BOM = TextFileBOM::UTF16_BE; return; }
	}

	// UTF8
	m_BOM = TextFileBOM::UTF8;
}

void Standard_Text::SetTextFileBOM(std::uintmax_t _Ptr)
{
	// Write BOM
	UCHAR _BomBytes[4]{};
	switch (m_BOM)
	{

	case TextFileBOM::UTF8:
		break;

	case TextFileBOM::UTF8_BOM:
		_BomBytes[0] = 0xEF;
		_BomBytes[1] = 0xBB;
		_BomBytes[2] = 0xBF;
		File().Write(_Ptr, _BomBytes, 3);
		break;

	case TextFileBOM::UTF16_LE:
		_BomBytes[0] = 0xFF;
		_BomBytes[1] = 0xFE;
		File().Write(_Ptr, _BomBytes, 2);
		break;

	case TextFileBOM::UTF16_BE:
		_BomBytes[0] = 0xFE;
		_BomBytes[1] = 0xFF;
		File().Write(_Ptr, _BomBytes, 2);
		break;

	case TextFileBOM::UTF32_LE:
		_BomBytes[0] = 0xFF;
		_BomBytes[1] = 0xFE;
		_BomBytes[2] = 0x00;
		_BomBytes[3] = 0x00;
		File().Write(_Ptr, _BomBytes, 4);
		break;

	case TextFileBOM::UTF32_BE:
		_BomBytes[0] = 0x00;
		_BomBytes[1] = 0x00;
		_BomBytes[2] = 0xFE;
		_BomBytes[3] = 0xFF;
		File().Write(_Ptr, _BomBytes, 4);
		break;

	case TextFileBOM::UTF7:
		_BomBytes[0] = 0x2B;
		_BomBytes[1] = 0x2F;
		_BomBytes[2] = 0x76;
		File().Write(_Ptr, _BomBytes, 3);
		break;

	case TextFileBOM::UTF1:
		_BomBytes[0] = 0xF7;
		_BomBytes[1] = 0x64;
		_BomBytes[2] = 0x4C;
		File().Write(_Ptr, _BomBytes, 3);
		break;

	case TextFileBOM::UTF_EBCDIC:
		_BomBytes[0] = 0xDD;
		_BomBytes[1] = 0x73;
		_BomBytes[2] = 0x66;
		_BomBytes[3] = 0x73;
		File().Write(_Ptr, _BomBytes, 4);
		break;

	case TextFileBOM::SCSU:
		_BomBytes[0] = 0x0E;
		_BomBytes[1] = 0xFE;
		_BomBytes[2] = 0xFF;
		File().Write(_Ptr, _BomBytes, 3);
		break;

	case TextFileBOM::BOCU_1:
		_BomBytes[0] = 0xFB;
		_BomBytes[1] = 0xEE;
		_BomBytes[2] = 0x28;
		File().Write(_Ptr, _BomBytes, 3);
		break;

	case TextFileBOM::GB_18030:
		_BomBytes[0] = 0x84;
		_BomBytes[1] = 0x31;
		_BomBytes[2] = 0x95;
		_BomBytes[3] = 0x33;
		File().Write(_Ptr, _BomBytes, 4);
		break;

	case TextFileBOM::Unknown:
		Message(FormatCStyle("Standard Text File: Error, unknown Byte Order Mark was specified when trying to open or create: %s", File().GetPath().filename().string().c_str()));
		return;

	}
}

String Standard_Text::GetBOMStr(void)
{
	switch (m_BOM)
	{
	case TextFileBOM::UTF8: return "UTF-8";
	case TextFileBOM::UTF8_BOM: return "UTF-8 with BOM";
	case TextFileBOM::UTF16_LE: return "UTF-16 Little Endian";
	case TextFileBOM::UTF16_BE: return "UTF-16 Big Endian";
	case TextFileBOM::UTF32_LE: return "UTF-32 Little Endian";
	case TextFileBOM::UTF7: return "UTF-7";
	case TextFileBOM::UTF1: return "UTF-1";
	case TextFileBOM::UTF_EBCDIC: return "UTF-EBCDIC";
	case TextFileBOM::SCSU: return "SCSU";
	case TextFileBOM::BOCU_1: return "BOCU-1";
	case TextFileBOM::GB_18030: return "GB 18030";
	}
	return "Unknown";
}

StringW Standard_Text::GetBOMStrW(void)
{
	switch (m_BOM)
	{
	case TextFileBOM::UTF8: return L"UTF-8";
	case TextFileBOM::UTF8_BOM: return L"UTF-8 with BOM";
	case TextFileBOM::UTF16_LE: return L"UTF-16 Little Endian";
	case TextFileBOM::UTF16_BE: return L"UTF-16 Big Endian";
	case TextFileBOM::UTF32_LE: return L"UTF-32 Little Endian";
	case TextFileBOM::UTF7: return L"UTF-7";
	case TextFileBOM::UTF1: return L"UTF-1";
	case TextFileBOM::UTF_EBCDIC: return L"UTF-EBCDIC";
	case TextFileBOM::SCSU: return L"SCSU";
	case TextFileBOM::BOCU_1: return L"BOCU-1";
	case TextFileBOM::GB_18030: return L"GB 18030";
	}
	return L"Unknown";
}

String32 Standard_Text::GetBOMStr32(void)
{
	switch (m_BOM)
	{
	case TextFileBOM::UTF8: return U"UTF-8";
	case TextFileBOM::UTF8_BOM: return U"UTF-8 with BOM";
	case TextFileBOM::UTF16_LE: return U"UTF-16 Little Endian";
	case TextFileBOM::UTF16_BE: return U"UTF-16 Big Endian";
	case TextFileBOM::UTF32_LE: return U"UTF-32 Little Endian";
	case TextFileBOM::UTF7: return U"UTF-7";
	case TextFileBOM::UTF1: return U"UTF-1";
	case TextFileBOM::UTF_EBCDIC: return U"UTF-EBCDIC";
	case TextFileBOM::SCSU: return U"SCSU";
	case TextFileBOM::BOCU_1: return U"BOCU-1";
	case TextFileBOM::GB_18030: return U"GB 18030";
	}
	return U"Unknown";
}

std::size_t Standard_Text::GetLineCount(void)
{
	if (validUTF8())
	{
		return UTF8().Line.size();
	}
	else if (validUTF16())
	{
		return UTF16().Line.size();
	}
	else if (validUTF32())
	{
		return UTF32().Line.size();
	}
	return 0;
}

String Standard_Text::GetLine(std::size_t Line_No)
{
	if (validUTF8())
	{
		if (Line_No < UTF8().Line.size())
		{
			return UTF8().Line[Line_No];
		}
	}
	return std::string();
}

StringW Standard_Text::GetLineW(std::size_t Line_No)
{
	if (validUTF16())
	{
		if (Line_No < UTF16().Line.size())
		{
			return UTF16().Line[Line_No];
		}
	}
	return std::wstring();
}

String32 Standard_Text::GetLine32(std::size_t Line_No)
{
	if (validUTF32())
	{
		if (Line_No < UTF32().Line.size())
		{
			return UTF32().Line[Line_No];
		}
	}
	return std::u32string();
}

StrVec Standard_Text::GetArgs(std::size_t Line_No)
{
	if (validUTF8())
	{
		if (Line_No < UTF8().Line.size())
		{
			return GetStrVec(UTF8().Line[Line_No].c_str());
		}
	}
	return StrVec();
}

StrVecW Standard_Text::GetArgsW(std::size_t Line_No)
{
	if (validUTF16())
	{
		if (Line_No < UTF16().Line.size())
		{
			return GetStrVec(UTF16().Line[Line_No].c_str());
		}
	}
	return StrVecW();
}

StrVec32 Standard_Text::GetArgs32(std::size_t Line_No)
{
	if (validUTF32())
	{
		if (Line_No < UTF32().Line.size())
		{
			return GetStrVec(UTF32().Line[Line_No].c_str());
		}
	}
	return StrVec32();
}

void Standard_Text::AddLine(const std::string _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vsnprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(char));
	std::vector<char> String(_StrLen);
	std::vsnprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	m_UTF8.get()->Line.push_back(String.data());
}

void Standard_Text::AddLine(const std::wstring _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vswprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	m_UTF16.get()->Line.push_back(String.data());
}

void Standard_Text::AddEndLine(void)
{
	if (validUTF8())
	{
		m_UTF8.get()->Line.push_back("\r");		// 0x0D
		//m_UTF8.get()->Line.push_back("\n");	// 0x0A
	}
	else if (validUTF16())
	{
		m_UTF16.get()->Line.push_back(L"\r");	// 0x0D
		//m_UTF16.get()->Line.push_back(L"\n");	// 0x0A
	}
	else if (validUTF32())
	{
		m_UTF32.get()->Line.push_back(U"\r");	// 0x0D
		//m_UTF32.get()->Line.push_back(U"\n");	// 0x0A
	}
}

bool Standard_Text::FlushUTF8(void)
{
	if (validUTF8())
	{
		std::uintmax_t _Ptr = 0;
		for (auto& Line : m_UTF8.get()->Line)
		{
			_Ptr = File().WriteStr(_Ptr, Line, false);
		}
	}
	return true;
}

bool Standard_Text::FlushUTF16(void)
{
	if (validUTF16())
	{
		std::uintmax_t _Ptr = 2;
		for (auto& Line : m_UTF16.get()->Line)
		{
			_Ptr = File().WriteStr(_Ptr, Line, false);
		}
	}
	return true;
}

bool Standard_Text::FlushUTF32(void)
{
	if (validUTF32())
	{
		std::uintmax_t _Ptr = 4;
		for (auto& Line : m_UTF32.get()->Line)
		{
			_Ptr = File().WriteStr(_Ptr, Line, false);
		}
	}
	return true;
}

void Standard_Text::OpenTextFileA(std::uintmax_t _Ptr) try
{
	if (!validUTF8()) { m_UTF8 = std::make_unique<TextFileUTF8>(); }

	std::uintmax_t _FileSize = File().Size();

	std::string _String;

	do {

		File().ReadStr(_Ptr, _String);

		if (_String.empty()) { _Ptr += 1; continue; }

		UTF8().Line.push_back(_String);

		_Ptr += _String.size();

	} while ((_Ptr < _FileSize) && (!File().eof()));

}
catch (...) { Exception(std::current_exception()); }

void Standard_Text::OpenTextFileW(std::uintmax_t _Ptr) try
{
	if (!validUTF16()) { m_UTF16 = std::make_unique<TextFileUTF16>(); }

	std::uintmax_t _FileSize = File().Size();

	std::wstring _String;

	do {

		File().ReadStr(_Ptr, _String, (m_BOM == TextFileBOM::UTF16_BE) ? true : false);

		if (_String.empty()) { _Ptr += sizeof(std::wint_t); continue; }

		UTF16().Line.push_back(_String);

		_Ptr += _String.size() * sizeof(std::wint_t);

	} while ((_Ptr < _FileSize) && (!File().eof()));

}
catch (...) { Exception(std::current_exception()); }

void Standard_Text::OpenTextFile32(std::uintmax_t _Ptr) try
{
	if (!validUTF32()) { m_UTF32 = std::make_unique<TextFileUTF32>(); }

	std::uintmax_t _FileSize = File().Size();

	std::u32string _String;

	do {

		File().ReadStr(_Ptr, _String, (m_BOM == TextFileBOM::UTF32_BE) ? true : false);

		if (_String.empty()) { _Ptr += sizeof(char32_t); continue; }

		UTF32().Line.push_back(_String);

		_Ptr += _String.size() * sizeof(char32_t);

	} while ((_Ptr < _FileSize) && (!File().eof()));

}
catch (...) { Exception(std::current_exception()); }

bool Standard_Text::Open(std::filesystem::path _Filename, FileAccessMode e_Mode, std::uintmax_t _Ptr) try
{
	// File Access Mode constants
	static constexpr int READ = std::to_underlying(FileAccessMode::Read);
	static constexpr int WRITE = std::to_underlying(FileAccessMode::Write);
	static constexpr int APPEND = std::to_underlying(FileAccessMode::Append);
	static constexpr int READ_EX = std::to_underlying(FileAccessMode::Read_Ex);
	static constexpr int WRITE_EX = std::to_underlying(FileAccessMode::Write_Ex);
	static constexpr int APPEND_EX = std::to_underlying(FileAccessMode::Append_Ex);

	// Close file and clear memory
	Close();

	// Create file object
	if (!validFile()) { m_File = std::make_unique<StdFile>(); }

	// Skip BOM?
	bool b_SkipBOM = ((std::to_underlying(m_BOM) & std::to_underlying(TextFileBOM::Skip)) == std::to_underlying(TextFileBOM::Skip));
	if (b_SkipBOM)
	{
		m_BOM = static_cast<TextFileBOM>(std::to_underlying(m_BOM) & ~std::to_underlying(TextFileBOM::Skip));
	}

	// Does file exist?
	bool b_Exists = File().Exists(File().CleanPath(_Filename));

	// Read/Write BOM and Open/Create file
	switch (std::to_underlying(e_Mode) & (READ | WRITE | APPEND | READ_EX | WRITE_EX | APPEND_EX))
	{

	case READ:
	case READ_EX:

		// Open File
		File().Open(_Filename, e_Mode, false, false);
		if (!File())
		{
			//Message(FormatCStyle("Standard Text File: Error, could not open %s", _Filename.filename().string().c_str()));
			m_BOM = TextFileBOM::Unknown;
			return false;
		}

		// Read BOM
		if (!b_SkipBOM) { GetTextFileBOM(_Ptr); }

		// Create text object and parse file
		switch (m_BOM)
		{
		case TextFileBOM::UTF8:
			OpenTextFileA(_Ptr);
			return true;
		case TextFileBOM::UTF8_BOM:
			if (!b_SkipBOM) { _Ptr += 3; }
			OpenTextFileA(_Ptr);
			return true;
		case TextFileBOM::UTF16_LE:
		case TextFileBOM::UTF16_BE:
			if (!b_SkipBOM) { _Ptr += 2; }
			OpenTextFileW(_Ptr);
			return true;
		case TextFileBOM::UTF32_LE:
		case TextFileBOM::UTF32_BE:
			if (!b_SkipBOM) { _Ptr += 4; }
			OpenTextFile32(_Ptr);
			return true;
		case TextFileBOM::UTF7:
		case TextFileBOM::UTF1:
		case TextFileBOM::UTF_EBCDIC:
		case TextFileBOM::SCSU:
		case TextFileBOM::BOCU_1:
		case TextFileBOM::GB_18030:
		case TextFileBOM::Unknown:
			Close();
			Message(FormatCStyle("Standard Text File: Error, unsupported text encoding: %s", GetBOMStr().c_str()));
			return false;
		}

		break;

	case WRITE:
	case WRITE_EX:

		// Open File
		File().Open(_Filename, e_Mode, false, true);
		if (!File())
		{
			//Message(FormatCStyle("Standard Text File: Error, could not create %s", _Filename.filename().string().c_str()));
			m_BOM = TextFileBOM::Unknown;
			return false;
		}

		// Write BOM
		if (!b_SkipBOM) { SetTextFileBOM(_Ptr); }

		// Create text object
		switch (m_BOM)
		{
		case TextFileBOM::UTF8:
		case TextFileBOM::UTF8_BOM:
			if (!validUTF8()) { m_UTF8 = std::make_unique<TextFileUTF8>(); }
			return true;
		case TextFileBOM::UTF16_LE:
		case TextFileBOM::UTF16_BE:
			if (!validUTF16()) { m_UTF16 = std::make_unique<TextFileUTF16>(); }
			return true;
		case TextFileBOM::UTF32_LE:
		case TextFileBOM::UTF32_BE:
			if (!validUTF32()) { m_UTF32 = std::make_unique<TextFileUTF32>(); }
			return true;
		case TextFileBOM::UTF7:
		case TextFileBOM::UTF1:
		case TextFileBOM::UTF_EBCDIC:
		case TextFileBOM::SCSU:
		case TextFileBOM::BOCU_1:
		case TextFileBOM::GB_18030:
		case TextFileBOM::Unknown:
			Close();
			Message(FormatCStyle("Standard Text File: Error, unsupported text encoding: %s", GetBOMStr().c_str()));
			return false;
		}

		break;

	case APPEND:
	case APPEND_EX:

		// Open File
		File().Open(_Filename, e_Mode, false, false);
		if (!File())
		{
			//Message(FormatCStyle("Standard Text File: Error, could not open or create %s", _Filename.filename().string().c_str()));
			m_BOM = TextFileBOM::Unknown;
			return false;
		}

		// Write BOM if file doesn't exist
		if ((!b_Exists) && (!b_SkipBOM)) { SetTextFileBOM(_Ptr); }

		// Create text object
		switch (m_BOM)
		{
		case TextFileBOM::UTF8:
		case TextFileBOM::UTF8_BOM:
			if (!validUTF8()) { m_UTF8 = std::make_unique<TextFileUTF8>(); }
			return true;
		case TextFileBOM::UTF16_LE:
		case TextFileBOM::UTF16_BE:
			if (!validUTF16()) { m_UTF16 = std::make_unique<TextFileUTF16>(); }
			return true;
		case TextFileBOM::UTF32_LE:
		case TextFileBOM::UTF32_BE:
			if (!validUTF32()) { m_UTF32 = std::make_unique<TextFileUTF32>(); }
			return true;
		case TextFileBOM::UTF7:
		case TextFileBOM::UTF1:
		case TextFileBOM::UTF_EBCDIC:
		case TextFileBOM::SCSU:
		case TextFileBOM::BOCU_1:
		case TextFileBOM::GB_18030:
		case TextFileBOM::Unknown:
			Close();
			Message(FormatCStyle("Standard Text File: Error, unsupported text encoding: %s", GetBOMStr().c_str()));
			return false;
		}

		break;

	}

	return false;
}
catch (...) { Exception(std::current_exception()); return false; }

void Standard_Text::Close(void) noexcept
{
	if (validFile())
	{
		File().Close();
	}
	if (validUTF8())
	{
		for (auto& Line : UTF8().Line) { Line.clear(); }
		UTF8().Line.clear();
	}
	if (validUTF16())
	{
		for (auto& Line : UTF16().Line) { Line.clear(); }
		UTF16().Line.clear();
	}
	if (validUTF32())
	{
		for (auto& Line : UTF32().Line) { Line.clear(); }
		UTF32().Line.clear();
	}

	m_UTF8.reset();
	m_UTF16.reset();
	m_UTF32.reset();
	m_File.reset();
}