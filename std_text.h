/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
* 
*		Keep track of the file pointer for each line in the file
*
*/


#pragma once


#include "std_exception.h"

#include "std_string.h"

#include "std_basic_fstream.h"


/*
	Standard Text File
 
	Examples:
		StdText MyFile { "MyFile.txt" };	// Open file for reading and writing, auto-detect encoding, load file into memory
		StdText MyFile { "MyFile.txt", FileAccessMode::Write, TextFileBOM::UTF16_LE };	// Create file for writing, UTF16 Little Endian
		StdText MyFile { "MyFile.txt", FileAccessMode::Read, TextFileBOM::UTF16_BE | TextFileBOM::Skip, 0x100 };	// UTF16 Big Endian, skip BOM and start reading at 0x100
*/
typedef class Standard_Text StdText;


// Text File Data (UTF8)
typedef struct tagTextFileUTF8 {
	StrVec Line;
} TextFileUTF8;

// Text File Data (UTF16)
typedef struct tagTextFileUTF16 {
	StrVecW Line;
} TextFileUTF16;

// Text File Data (UTF32)
typedef struct tagTextFileUTF32 {
	StrVec32 Line;
} TextFileUTF32;


/*
	Text File Byte Order Mark

	https://en.wikipedia.org/wiki/Byte_order_mark
*/
enum class TextFileBOM : int
{
	//	Func Parameter		// Description
	UTF8 = 1 << 0,			// UTF-8
	UTF8_BOM = 1 << 1,		// UTF-8 with Byte Order Mark
	UTF16_LE = 1 << 2,		// UTF-16 Little Endian
	UTF16_BE = 1 << 3,		// UTF-16 Big Endian
	UTF32_LE = 1 << 4,		// UTF-32 Little Endian
	UTF32_BE = 1 << 5,		// UTF-32 Big Endian
	UTF7 = 1 << 6,			// UTF-7
	UTF1 = 1 << 7,			// UTF-1
	UTF_EBCDIC = 1 << 8,	// UTF-EBCDIC
	SCSU = 1 << 9,			// SCSU
	BOCU_1 = 1 << 10,		// BOCU-1
	GB_18030 = 1 << 11,		// GB 18030
	Skip = 31,				// Skip reading/writing of the Byte Order Mark
	Unknown = -1			// Unknown Encoding
};

static TextFileBOM operator | (TextFileBOM _Mode0, TextFileBOM _Mode1)
{
	return static_cast<TextFileBOM>(std::to_underlying(_Mode0) | std::to_underlying(_Mode1));
}


/*
	Text Files (*.txt)
*/
class Standard_Text :
	protected Standard_String {
private:

	// StdFile Object
	std::unique_ptr<StdFile> m_File { nullptr };

	// Byte Order Mark
	TextFileBOM m_BOM { TextFileBOM::Unknown };

	// Text File Data (UTF8)
	std::unique_ptr<TextFileUTF8> m_UTF8 { nullptr };

	// Text File Data (UTF16)
	std::unique_ptr<TextFileUTF16> m_UTF16 { nullptr };

	// Text File Data (UTF32)
	std::unique_ptr<TextFileUTF32> m_UTF32 { nullptr };

	// Is StdFile object valid?
	[[nodiscard]] constexpr bool validFile(void) const noexcept { return m_File.get() != nullptr; }

	// Is UTF8 object valid?
	[[nodiscard]] constexpr bool validUTF8(void) const noexcept { return m_UTF8.get() != nullptr; }

	// Is UTF16 object valid?
	[[nodiscard]] constexpr bool validUTF16(void) const noexcept { return m_UTF16.get() != nullptr; }

	// Is UTF32 object valid?
	[[nodiscard]] constexpr bool validUTF32(void) const noexcept { return m_UTF32.get() != nullptr; }

	// Is UTF8 buffer empty?
	[[nodiscard]] constexpr bool emptyUTF8() const noexcept { return validUTF8() ? m_UTF8.get()->Line.empty() : true; }

	// Is UTF16 buffer empty?
	[[nodiscard]] constexpr bool emptyUTF16() const noexcept { return validUTF16() ? m_UTF16.get()->Line.empty() : true; }

	// Is UTF32 buffer empty?
	[[nodiscard]] constexpr bool emptyUTF32() const noexcept { return validUTF32() ? m_UTF32.get()->Line.empty() : true; }

	// StdFile Object
	[[nodiscard]] constexpr auto File() const noexcept -> StdFile& { return *m_File.get(); }

	// UTF8 Object
	[[nodiscard]] constexpr auto UTF8() const noexcept -> TextFileUTF8& { return *m_UTF8.get(); }

	// UTF16 Object
	[[nodiscard]] constexpr auto UTF16() const noexcept -> TextFileUTF16& { return *m_UTF16.get(); }

	// UTF32 Object
	[[nodiscard]] constexpr auto UTF32() const noexcept -> TextFileUTF32& { return *m_UTF32.get(); }

	// Get Byte Order Mark
	void GetTextFileBOM(std::uintmax_t _Ptr = 0);

	// Set Byte Order Mark
	void SetTextFileBOM(std::uintmax_t _Ptr = 0);

	// Open Text File (UTF8)
	void OpenTextFileA(std::uintmax_t _Ptr = 0);

	// Open Text File (UTF16)
	void OpenTextFileW(std::uintmax_t _Ptr = 0);

	// Open Text File (UTF32)
	void OpenTextFile32(std::uintmax_t _Ptr = 0);

	// Copy
	Standard_Text(const Standard_Text&) = delete;
	Standard_Text& operator = (const Standard_Text&) = delete;

public:

	using Standard_String::GetStrVec;
	using Standard_String::CleanString;
	using Standard_String::Message;
	using Standard_String::FormatCStyle;
	using Standard_String::ToUpper;
	using Standard_String::ToLower;

	/*
		Construction
	*/
	explicit Standard_Text(std::filesystem::path _Filename, FileAccessMode e_Mode = FileAccessMode::Read_Ex, TextFileBOM e_BOM = TextFileBOM::Unknown, std::streampos _Ptr = 0) :
		m_File(nullptr),
		m_BOM(e_BOM),
		m_UTF8(nullptr),
		m_UTF16(nullptr),
		m_UTF32(nullptr)
	{
		Open(_Filename, e_Mode, _Ptr);
	}

	explicit constexpr Standard_Text(void) :
		m_File(nullptr),
		m_BOM(TextFileBOM::Unknown),
		m_UTF8(nullptr),
		m_UTF16(nullptr),
		m_UTF32(nullptr) {}


	/*
		Deconstruction
	*/
	virtual ~Standard_Text(void) noexcept { Close(); }


	/*
		Move
	*/
	Standard_Text(Standard_Text&& _Other) noexcept :
		m_File(std::exchange(_Other.m_File, nullptr)),
		m_BOM(std::exchange(_Other.m_BOM, TextFileBOM::Unknown)),
		m_UTF8(std::exchange(_Other.m_UTF8, nullptr)),
		m_UTF16(std::exchange(_Other.m_UTF16, nullptr)),
		m_UTF32(std::exchange(_Other.m_UTF32, nullptr)) {}
	Standard_Text& operator=(Standard_Text&& _Other) noexcept
	{
		if (this != &_Other)
		{
			std::swap(m_File, _Other.m_File);
			std::swap(m_BOM, _Other.m_BOM);
			std::swap(m_UTF8, _Other.m_UTF8);
			std::swap(m_UTF16, _Other.m_UTF16);
			std::swap(m_UTF32, _Other.m_UTF32);
		}
		return *this;
	}


	/*
		Operator
	*/
	bool operator !()
	{
		if(!validUTF8() && !validUTF16() && !validUTF32()) { return true; }
		return false;
	}

	explicit operator bool(void) const noexcept { return File().IsOpen(); }


	/*
		Is open?
	*/
	[[nodiscard]] bool IsOpen(void) const noexcept
	{
		if (validUTF8() || validUTF16() || validUTF32()) { return true; }
		return false;
	}


	/*
		Initialize file for Read (auto-detect BOM), Write or Append (create BOM, if necessary) 
		On Read/Read_Ex, file is loaded into memory
	*/
	bool Open(std::filesystem::path _Filename, FileAccessMode e_Mode, std::uintmax_t _Ptr = 0);


	/*
		Close file and clear memory
		Called on deconstruction and Open()
	*/
	void Close(void) noexcept;


	/*
		Set Byte Order Mark
	*/
	void SetBOM(TextFileBOM e_BOM) { m_BOM = e_BOM; }


	/*
		Get Byte Order Mark (String)
	*/
	String GetBOMStr(void);

	
	/*
		Get Byte Order Mark (Wide String)
	*/
	StringW GetBOMStrW(void);


	/*
		Get Byte Order Mark (32-bit String)
	*/
	String32 GetBOMStr32(void);


	/*
		Get total line count
	*/
	std::size_t GetLineCount(void);


	/*
		Get line (String)
	*/
	String GetLine(std::size_t Line_No);


	/*
		Get line (Wide String)
	*/
	StringW GetLineW(std::size_t Line_No);


	/*
		Get line (32-bit String)
	*/
	String32 GetLine32(std::size_t Line_No);


	/*
		Get line arguments (String)
	*/
	StrVec GetArgs(std::size_t Line_No);


	/*
		Get line arguments (Wide String)
	*/
	StrVecW GetArgsW(std::size_t Line_No);


	/*
		Get line arguments (32-bit String)
	*/
	StrVec32 GetArgs32(std::size_t Line_No);


	/*
		Add line (C-Style formatted String)
	*/
	void AddLine(const std::string _Format, ...);


	/*
		Add line (C-Style formatted Wide String)
	*/
	void AddLine(const std::wstring _Format, ...);


	/*
		Add line (C-Style formatted 32-bit String)
	*/
	//void AddLine(const std::u32string _Format, ...);


	/*
		Add end line
	*/
	void AddEndLine(void);


	/*
		Flush contents to file
	*/
	void FlushUTF8(void);


	/*
		Flush contents to file
	*/
	void FlushUTF16(void);


	/*
		Flush contents to file
	*/
	void FlushUTF32(void);


};