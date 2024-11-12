/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*		Maybe some cast converstions for tellg and tellp?
* 
*		File date functions
* 
*		Crc class needs to be moved out of the file class
*
*/


#pragma once

#include "std_filesystem.h"

#include "std_crc32.h"

#include <fstream>


/*
	Standard Basic File Stream

	Example:
		StdFile MyFile { "MyFile.txt", FileAccessMode::Read, false };

	Example:
		StdFile MyFile;
		MyFile.Open("MyFile.txt", FileAccessMode::Read, false);

	Example:
		std::unique_ptr<StdFile> MyFile = std::make_unique<StdFile>();
		MyFile.get()->Open("MyFile.txt", FileAccessMode::Read, false);
*/
typedef class Standard_Basic_FStream StdFile;


/*
	File Access Mode

	https://en.cppreference.com/w/cpp/io/basic_fstream/open
*/
enum class FileAccessMode : int
{
	//	Func Parameter			// ASCII	// Explanation						// If File Exists					// If File Doesn't Exists
	Read = 1 << 0,				// "r"		// Open a file for reading			// read from start					// return NULL and set error
	Write = 1 << 1,				// "w"		// Create a file for writing		// destroy contents					// create new
	Append = 1 << 2,			// "a"		// Append to a file					// write to end						// create new
	Read_Ex = 1 << 3,			// "r+"		// Open a file for read/write		// read from start					// return NULL and set error
	Write_Ex = 1 << 4,			// "w+"		// Create a file for read/write		// destroy contents					// create new
	Append_Ex = 1 << 5,			// "a+"		// Open a file for read/write		// write to end						// create new
	No_Create = 1 << 6,			// 			// Open only if file exists			// regular write/append behavior	// return NULL and set error
	No_Replace = 1 << 7,		// "wx"		// Don't overwrite existing file	// return NULL and set error		// regular write/append behavior
	Unknown = -1				// 			// Do nothing						// return NULL and set error		// return NULL and set error
};

static FileAccessMode operator | (FileAccessMode _Mode0, FileAccessMode _Mode1)
{
	return static_cast<FileAccessMode>(std::to_underlying(_Mode0) | std::to_underlying(_Mode1));
}


/*
	If true (1), functions in the StdFile class will check if the file is open before performing an operation
*/
#define FILEOPEN_CHECK  0


/*
	If true (1), write functions in the StdFile class will immediately flush uncommitted changes
*/
#define FILEWRITE_FLUSH  0


/*
	If true (1), read functions in the StdFile class will immediately synchronize the data source
*/
#define FILEREAD_SYNC  0


/*
	https://en.cppreference.com/w/cpp/io/basic_fstream
*/
class Standard_Basic_FStream final :
	protected Standard_FileSystem,
	protected Cyclic_Redundancy_Check {
private:

	// File Access Mode constants
	static constexpr int READ = std::to_underlying(FileAccessMode::Read);
	static constexpr int WRITE = std::to_underlying(FileAccessMode::Write);
	static constexpr int APPEND = std::to_underlying(FileAccessMode::Append);
	static constexpr int READ_EX = std::to_underlying(FileAccessMode::Read_Ex);
	static constexpr int WRITE_EX = std::to_underlying(FileAccessMode::Write_Ex);
	static constexpr int APPEND_EX = std::to_underlying(FileAccessMode::Append_Ex);
	static constexpr int NO_CREATE = std::to_underlying(FileAccessMode::No_Create);
	static constexpr int NO_REPLACE = std::to_underlying(FileAccessMode::No_Replace);

	// File Stream
	std::unique_ptr<std::fstream> m_File { nullptr };

	// Filesystem Path
	std::unique_ptr<std::filesystem::path> m_Path { nullptr };

	// File Access Mode
	FileAccessMode m_Mode { FileAccessMode::Unknown };

	// Open file stream in binary mode?
	bool m_Binary { false };

	// Discard all contents of the file stream when creating? (Write mode only, Write_Ex always truncates)
	bool m_Truncate { false };

	// Is the file stream valid?
	[[nodiscard]] constexpr bool validFile() const noexcept { return m_File.get() != nullptr; }

	// Is the filesystem path valid?
	[[nodiscard]] constexpr bool validPath() const noexcept { return m_Path.get() != nullptr; }

	// Get the StdFile object's file stream
	[[nodiscard]] constexpr auto File() noexcept -> std::fstream&
	{
		if (m_File.get() == nullptr)
		{
			m_File = std::make_unique<std::fstream>();
		}
		return *m_File.get();
	}

	// Get the StdFile object's filesystem path
	[[nodiscard]] constexpr auto Path() noexcept -> std::filesystem::path&
	{
		if (m_Path.get() == nullptr)
		{
			m_Path = std::make_unique<std::filesystem::path>();
		}
		return *m_Path.get();
	}

	// Open File Stream
	[[nodiscard]] std::fstream open(std::filesystem::path _Filename, FileAccessMode e_Mode = FileAccessMode::Write_Ex, bool b_Binary = true, bool b_Truncate = true);

	// Read
	std::uintmax_t read(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize);

	// Write
	std::uintmax_t write(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize);

	// Read Next
	void readNext(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize);

	// Write Next
	void writeNext(std::fstream& _File, std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize);

	// Read String
	std::uintmax_t readStr(std::fstream& _File, std::uintmax_t _Ptr, String& _OutStr, UCharVec _DelimiterList);
	std::uintmax_t readStr(std::fstream& _File, std::uintmax_t _Ptr, StringW& _OutStr, bool b_SwapBytes, std::vector<std::wint_t> _DelimiterList);
	std::uintmax_t readStr(std::fstream& _File, std::uintmax_t _Ptr, String32& _OutStr, bool b_SwapBytes, std::vector<char32_t> _DelimiterList);

	// Write String
	std::uintmax_t writeStr(std::fstream& _File, std::uintmax_t _Ptr, String _String, bool b_NullTerminator);
	std::uintmax_t writeStr(std::fstream& _File, std::uintmax_t _Ptr, StringW _String, bool b_NullTerminator);
	std::uintmax_t writeStr(std::fstream& _File, std::uintmax_t _Ptr, String32 _String, bool b_NullTerminator);

	// Find
	std::uintmax_t find(void* _Data, std::uintmax_t _ElementSize, std::uintmax_t _PtrStart, std::uintmax_t _PtrEnd);

	// File Size
	[[nodiscard]] std::uintmax_t size(std::fstream& _File);

	// File Position
	[[nodiscard]] std::uintmax_t tell(std::fstream& _File);

	// Copy
	Standard_Basic_FStream(const Standard_Basic_FStream&) = delete;
	Standard_Basic_FStream& operator = (const Standard_Basic_FStream&) = delete;

	// Inheritance
	using Standard_FileSystem::ResizeFile;
	using Standard_FileSystem::GetFileName;
	using Standard_FileSystem::SetFileName;
	using Standard_FileSystem::GetFileStem;
	using Standard_FileSystem::GetFileExtension;
	using Standard_FileSystem::SetFileExtension;

public:


	/*
		Construction
	*/
	explicit Standard_Basic_FStream(std::filesystem::path _Filename, FileAccessMode e_Mode = FileAccessMode::Write_Ex, bool b_Binary = true, bool b_Truncate = true) :
		m_File(nullptr),
		m_Path(std::make_unique<std::filesystem::path>(CleanPath(_Filename))),
		m_Mode(e_Mode),
		m_Binary(b_Binary),
		m_Truncate(b_Truncate)
	{
		m_File = std::make_unique<std::fstream>(open(Path(), m_Mode, m_Binary, m_Truncate));
	}

	explicit Standard_Basic_FStream(void) noexcept = default;


	/*
		Deconstruction
	*/
	virtual ~Standard_Basic_FStream(void) noexcept
	{
		if (validFile()) { File().close(); }
		if (validPath()) { Path().clear(); }
		m_File.reset();
		m_Path.reset();
	}


	/*
		Move
	*/
	Standard_Basic_FStream(Standard_Basic_FStream&& _Other) noexcept :
		m_File(std::exchange(_Other.m_File, std::make_unique<std::fstream>())),
		m_Path(std::exchange(_Other.m_Path, std::make_unique<std::filesystem::path>())),
		m_Mode(std::exchange(_Other.m_Mode, FileAccessMode::Unknown)),
		m_Binary(std::exchange(_Other.m_Binary, false)),
		m_Truncate(std::exchange(_Other.m_Truncate, false)) {}
	Standard_Basic_FStream& operator = (Standard_Basic_FStream&& _Other) noexcept
	{
		if (this != &_Other)
		{
			std::swap(m_File, _Other.m_File);
			std::swap(m_Path, _Other.m_Path);
			std::swap(m_Mode, _Other.m_Mode);
			std::swap(m_Binary, _Other.m_Binary);
			std::swap(m_Truncate, _Other.m_Truncate);
		}
		return *this;
	}


	/*
		Get the StdFile object's filesystem path
	*/
	operator std::filesystem::path() { return Path(); }


	/*
		Get the StdFile object's filesystem path as a string
	*/
	operator std::string() { return Path().string(); }


	/*
		Get the StdFile object's filesystem path as a wide string
	*/
	operator std::wstring() { return Path().wstring(); }


	/*
		Check if the file stream is open, good, error-free, and not at end-of-file
	*/
	bool operator !()
	{
		std::fstream& _File = File();
		if (!_File.is_open()) { return true; }
		if (!_File.good()) { return true; }
		if (_File.fail()) { return false; }
		if (_File.bad()) { return false; }
		return false;
	}


	/*
		Inheritance
	*/
	using Cyclic_Redundancy_Check::GetCRC32;
	using Standard_FileSystem::CleanPath;
	using Standard_FileSystem::Exists;
	using Standard_FileSystem::GetDirectory;
	using Standard_FileSystem::CreateDirectory;
	using Standard_FileSystem::GetCurrentWorkingDir;
	using Standard_FileSystem::SetCurrentWorkingDir;
	using Standard_FileSystem::GetTempDirectory;


	/*
		StdFile object's std::fstream
	*/
	[[nodiscard]] std::fstream& Get(void) { return File(); }


	/*
		Check if no error has occurred (I/O operations are available)
	*/
	[[nodiscard]] bool good(void) noexcept { return File().good(); }


	/*
		Check if end-of-file has been reached
	*/
	[[nodiscard]] bool eof(void) noexcept { return File().eof(); }


	/*
		Check if an error has occurred
	*/
	[[nodiscard]] bool fail(void) noexcept { return File().fail(); }


	/*
		Check if a non-recoverable error has occurred
	*/
	[[nodiscard]] bool bad(void) noexcept { return File().bad(); }


	/*
		Get the file stream as an unsigned char vector
	*/
	[[nodiscard]] std::vector<std::uint8_t> buffer(void);


	/*
		Set the file stream's buffer size
	*/
	void SetBufferSize(char* _Buffer, std::streamsize _Size) { File().rdbuf()->pubsetbuf(_Buffer, _Size); }


	/*
		Open file stream, assign the filesystem path, access mode, binary mode, and truncate flag to the current StdFile object
		Return true if the file was opened successfully
	*/
	bool Open(std::filesystem::path _Filename, FileAccessMode e_Mode = FileAccessMode::Write_Ex, bool b_Binary = true, bool b_Truncate = true);


	/*
		Reopen a file stream that has been previously closed
		Return true if the file was reopened successfully
	*/
	bool Reopen(FileAccessMode e_Mode = FileAccessMode::Write_Ex, bool b_Binary = true, bool b_Truncate = true);


	/*
		Check if the stream has an associated file
	*/
	bool IsOpen(void) noexcept { return File().is_open(); }


	/*
		Close the file stream
	*/
	void Close(void) { File().close(); }


	/*
		Get the size of the file stream in bytes
	*/
	[[nodiscard]] std::uintmax_t Size(void) { return size(File()); }


	/*
		Get the position of the file stream in bytes
	*/
	[[nodiscard]] std::uintmax_t Tell(void) { return tell(File()); }


	/*
		Get the position of the file stream in bytes
	*/
	[[nodiscard]] std::uintmax_t Position(void) { return tell(File()); }


	/*
		Resize the file stream to a specified size in bytes
		Return true if the file was resized successfully
	*/
	bool Resize(std::uintmax_t _Size) { return ResizeFile(Path(), _Size); }


	/*
		Resize the file stream to a specified block size in bytes
		Return true if the file was resized successfully
	*/
	bool ResizeAlign(std::uintmax_t _BlockSize);


	/*
		Align the file stream's position to a specified block size in bytes
	*/
	std::uintmax_t PosAlign(std::uintmax_t& _Ptr, std::uintmax_t BlockSize);


	/*
		Align any value to a specified block size in bytes
	*/
	template<typename T>
	T Align(T& _Value, std::uintmax_t BlockSize)
	{
		if (_Value % BlockSize)
		{
			_Value += static_cast<T>(BlockSize) - (_Value % static_cast<T>(BlockSize));
		}
		return _Value;
	}


	/*
		Get the CRC32 checksum of the file stream
	*/
	[[nodiscard]] std::uint32_t CRC32(void) { return CRC32(0, size(File())); }


	/*
		Read bytes from the file stream and get the CRC32 checksum of those bytes
	*/
	[[nodiscard]] std::uint32_t CRC32(std::uintmax_t _Ptr, std::uintmax_t _ElementSize);


	/*
		Get the CRC32 checksum of a data source
	*/
	[[nodiscard]] std::uint32_t CRC32(void* _Data, std::uintmax_t _ElementSize) const { return GetCRC32(_Data, _ElementSize); }


	/*
		Get the CRC32 checksum of a vector data source
	*/
	template<typename T, typename Traits = std::allocator_traits<T>>
	[[nodiscard]] std::uint32_t CRC32(std::vector<T, Traits> _Data) const { return GetCRC32(_Data.data(), _Data.size() * sizeof(T)); }


	/*
		Read data source from the file stream
		Return new file position
	*/
	std::uintmax_t Read(std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) { return read(File(), _Ptr, _Data, _ElementSize); }


	/*
		Write data source to the file stream
		Return new file position
	*/
	std::uintmax_t Write(std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) { return write(File(), _Ptr, _Data, _ElementSize); }


	/*
		Same as Read, but without error checking and new file position return
	*/
	void ReadNext(std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) { readNext(File(), _Ptr, _Data, _ElementSize); }


	/*
		Same as Write, but without error checking and new file position return
	*/
	void WriteNext(std::uintmax_t _Ptr, void* _Data, std::uintmax_t _ElementSize) { writeNext(File(), _Ptr, _Data, _ElementSize); }


	/*
		Read a string from the file stream
		Return new file position
	*/
	std::uintmax_t ReadStr(std::uintmax_t _Ptr, String& _OutStr, UCharVec _DelimiterList = { '\n', '\f', '\r', '\0', 0xFF }) { return readStr(File(), _Ptr, _OutStr, _DelimiterList); }


	/*
		Read a wide string from the file stream
		Return new file position
	*/
	std::uintmax_t ReadStr(std::uintmax_t _Ptr, StringW& _OutStr, bool b_SwapBytes = false, std::vector<std::wint_t> _DelimiterList = { L'\n', L'\f', L'\r', 0x0000, 0xFFFF }) { return readStr(File(), _Ptr, _OutStr, b_SwapBytes, _DelimiterList); }


	/*
		Read a U32 string from the file stream
		Return new file position
	*/
	std::uintmax_t ReadStr(std::uintmax_t _Ptr, String32& _OutStr, bool b_SwapBytes = false, std::vector<char32_t> _DelimiterList = { U'\n', U'\f', U'\r', 0x00000000, 0xFFFFFFFF }) { return readStr(File(), _Ptr, _OutStr, b_SwapBytes, _DelimiterList); }


	/*
		Write a string to the file stream
		Return new file position
	*/
	std::uintmax_t WriteStr(std::uintmax_t _Ptr, String _String, bool b_NullTerminator = true) { return writeStr(File(), _Ptr, _String, b_NullTerminator); }


	/*
		Write a wide string to the file stream
		Return new file position
	*/
	std::uintmax_t WriteStr(std::uintmax_t _Ptr, StringW _String, bool b_NullTerminator = true) { return writeStr(File(), _Ptr, _String, b_NullTerminator); }


	/*
		Write a U32 string to the file stream
		Return new file position
	*/
	std::uintmax_t WriteStr(std::uintmax_t _Ptr, String32 _String, bool b_NullTerminator = true) { return writeStr(File(), _Ptr, _String, b_NullTerminator); }


	/*
		Find the first occurrence of data source in the file stream
		Return file position of the first occurrence, or -1 if not found
	*/
	std::uintmax_t Find(void* _Data, std::uintmax_t _ElementSize, std::uintmax_t _PtrStart = 0, std::uintmax_t _PtrEnd = -1) { return find(_Data, _ElementSize, _PtrStart, _PtrEnd); }


	/*
		Find the first occurrence of vector data source in the file stream
		Return file position of the first occurrence, or -1 if not found
	*/
	template<typename T, typename Traits = std::allocator_traits<T>>
	std::uintmax_t Find(std::vector<T, Traits> _Data, std::uintmax_t _PtrStart = 0, std::uintmax_t _PtrEnd = -1)
	{
		return find(_Data.data(), _Data.size() * sizeof(T), _PtrStart, _PtrEnd);
	}


	/*
		Create a file on disk from a data source
		Return true if the file was created successfully
	*/
	bool Create(std::filesystem::path _Filename, void* _Source, std::uintmax_t _ElementSize, bool b_OverwriteExisting = true);


	/*
		Create a file on disk from a vector data source
		Return true if the file was created successfully
	*/
	template<typename T, typename Traits = std::allocator_traits<T>>
	bool Create(std::filesystem::path _Filename, std::vector<T, Traits> _Source, bool b_OverwriteExisting = true)
	{
		return Create(_Filename, _Source.data(), _Source.size() * sizeof(T), b_OverwriteExisting);
	}


	/*
		Get the StdFile object's filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetPath(void) { return Path(); }


	/*
		Set the StdFile object's filesystem path
	*/
	void SetPath(std::filesystem::path _NewPath) { Path() = _NewPath; }


	/*
		Get the directory from the StdFile object's filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetDirectory(void) { return GetDirectory(Path()); }


	/*
		Get the file stem and extension from the StdFile object's filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileName(void) { return GetFileName(Path()); }


	/*
		Set the file stem and extension for the StdFile object's filesystem path
	*/
	bool SetFileName(std::filesystem::path _NewName, bool bPathMustExist = true) { return SetFileName(Path(), _NewName, bPathMustExist); }


	/*
		Get the file stem from the StdFile object's filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileStem(void) { return GetFileStem(Path()); }


	/*
		Get the file extension from the StdFile object's filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileExtension(void) { return GetFileExtension(Path()); }


	/*
		Set the file extension for the StdFile object's filesystem path
	*/
	bool SetFileExtension(std::filesystem::path _NewExt, bool bPathMustExist = true) { return SetFileExtension(Path(), _NewExt, bPathMustExist); }


};