/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO:
*
*/


#include "std_filesystem.h"


/*
	Test Path for File Name
*/
bool Standard_FileSystem::TestForFileName(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return false; }
	if (!_Path.has_extension()) { return false; }
	if (!_Path.has_stem()) { return false; }
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Clean Directory Path
*/
std::filesystem::path Standard_FileSystem::CleanDirectoryPath(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return ""; }

	if (_Path.has_extension()) { _Path.remove_filename(); }

	if (!_Path.is_absolute()) { _Path = std::filesystem::current_path() / _Path; }

	_Path = std::filesystem::weakly_canonical(_Path);

	_Path.make_preferred();

	return _Path;
}
catch (...) { Exception(std::current_exception()); return ""; }


/*
	Clean Path
*/
std::filesystem::path Standard_FileSystem::CleanPath(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return _Path; }

	if (!_Path.is_absolute()) { _Path = std::filesystem::current_path() / _Path; }

	_Path = std::filesystem::weakly_canonical(_Path);

	_Path.make_preferred();

	return _Path;
}
catch (...) { Exception(std::current_exception()); return ""; }


/*
	Exists
*/
bool Standard_FileSystem::Exists(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return false; }
	return std::filesystem::exists(_Path);
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Determine if a filesystem path is a directory
*/
[[nodiscard]] bool Standard_FileSystem::IsDirectory(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return false; }
	return std::filesystem::is_directory(_Path);
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Determine if a filesystem path is a regular file
*/
[[nodiscard]] bool Standard_FileSystem::IsFile(std::filesystem::path _Path) try
{
	if (_Path.empty()) { return false; }
	return std::filesystem::is_regular_file(_Path);
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	File Size
*/
std::uintmax_t Standard_FileSystem::FileSize(std::filesystem::path _Path) try
{
	if (!Exists(_Path)) { return 0; }
	return std::filesystem::file_size(_Path);
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Resize File
*/
bool Standard_FileSystem::ResizeFile(std::filesystem::path _Path, std::uintmax_t _Size) try
{
	if (!Exists(_Path) || !TestForFileName(_Path)) { return false; }
	std::filesystem::resize_file(_Path, _Size);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Create Directory
*/
bool Standard_FileSystem::CreateDirectory(std::filesystem::path _Path) try
{
	_Path = CleanDirectoryPath(_Path);
	if (!Exists(_Path))
	{
		return std::filesystem::create_directories(_Path);
	}
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Rename File or Directory
*/
bool Standard_FileSystem::Rename(std::filesystem::path& _Path, std::filesystem::path _NewName, bool bPathMustExist) try
{
	if (_Path.empty() || _NewName.empty()) { return false; }
	if (bPathMustExist && !Exists(_Path)) { return false; }
	std::filesystem::rename(_Path, _NewName);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Set Current Working Directory
*/
bool Standard_FileSystem::SetCurrentWorkingDir(std::filesystem::path& _Path, bool bCreateIfDoesntExist) try
{
	_Path = CleanDirectoryPath(_Path);
	if (bCreateIfDoesntExist) { CreateDirectory(_Path); }
	if (!Exists(_Path)) { return false; }
	std::filesystem::current_path(_Path);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Copy file
*/
bool Standard_FileSystem::Copy(std::filesystem::path _Source, std::filesystem::path _Destination, bool bOverwrite) try
{
	if (!IsFile(_Source)) { return false; }
	std::filesystem::copy(_Source, _Destination, bOverwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::skip_existing);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Get list of regular files in directory
*/
std::vector<std::filesystem::path> Standard_FileSystem::GetFileList(std::filesystem::path _Path) try
{
	std::filesystem::path Dir = CleanDirectoryPath(_Path);

	if (!Exists(Dir)) { return {}; }

	std::vector<std::filesystem::path> Files;

	for (const auto& Entry : std::filesystem::directory_iterator(Dir))
	{
		if (std::filesystem::is_regular_file(Entry)) { Files.push_back(Entry.path()); }
	}

	return Files;
}
catch (...) { Exception(std::current_exception()); return {}; }


/*
	Get/Set File Name
*/
std::filesystem::path Standard_FileSystem::GetFileName(std::filesystem::path _Path) try
{
	if (TestForFileName(_Path)) { return _Path.filename(); }
	return L"";
}
catch (...) { Exception(std::current_exception()); return ""; }

bool Standard_FileSystem::SetFileName(std::filesystem::path& _Path, std::filesystem::path _NewName, bool bPathMustExist) try
{
	if (bPathMustExist && !Exists(_Path)) { return false; }
	if (!TestForFileName(_Path) || !TestForFileName(_NewName)) { return false; }
	_Path.replace_filename(_NewName);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Get File Stem (File Namebase)
*/
std::filesystem::path Standard_FileSystem::GetFileStem(std::filesystem::path _Path) try
{
	if (TestForFileName(_Path)) { return _Path.stem(); }
	return L"";
}
catch (...) { Exception(std::current_exception()); return ""; }


/*
	Get/Set File Extension
*/
std::filesystem::path Standard_FileSystem::GetFileExtension(std::filesystem::path _Path) try
{
	if (TestForFileName(_Path)) { return _Path.extension(); }
	return L"";
}
catch (...) { Exception(std::current_exception()); return ""; }

bool Standard_FileSystem::SetFileExtension(std::filesystem::path& _Path, std::filesystem::path _NewExt, bool bPathMustExist) try
{
	if (bPathMustExist && !Exists(_Path)) { return false; }
	if (!TestForFileName(_Path)) { return false; }
	_Path.replace_extension(_NewExt);
	return true;
}
catch (...) { Exception(std::current_exception()); return false; }


/*
	Set File Date
*/
void Standard_FileSystem::SetFileDate(std::filesystem::path _Path, std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long long, std::micro>> _FileTime) try
{
	if (!Exists(_Path)) { return; }
	auto MillisecondsUTC = std::chrono::duration_cast<std::chrono::milliseconds>(_FileTime.time_since_epoch() + 11644473600000ms).count();
	std::filesystem::file_time_type FileTime{ std::chrono::milliseconds(MillisecondsUTC) };
	std::filesystem::last_write_time(_Path, FileTime);
}
catch (...) { Exception(std::current_exception()); }

void Standard_FileSystem::SetFileDateToNow(std::filesystem::path _Path) try
{
	if (!Exists(_Path)) { return; }
	auto MillisecondsUTC = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() + 11644473600000ms).count();
	std::filesystem::file_time_type FileTime{ std::chrono::milliseconds(MillisecondsUTC) };
	std::filesystem::last_write_time(_Path, FileTime);
}
catch (...) { Exception(std::current_exception()); }

bool Standard_FileSystem::SetFileDateWin(std::filesystem::path _Path, WORD Year, WORD Month, WORD Day, WORD Hour, WORD Minute, WORD Second, WORD Milliseconds) {

#ifdef _WINDOWS

	// Error
	if (!Exists(_Path)) { return false; }

	// Variable
	FILETIME FILE_TIME{};
	SYSTEMTIME SYS_TIME{};
	bool b_Result = false;

	// Open
	HANDLE hFile = CreateFileW(_Path.wstring().c_str(),
		FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) { return false; }

	// System Time
	GetSystemTime(&SYS_TIME);

	// Set Time
	SYS_TIME.wYear = Year;
	SYS_TIME.wMonth = Month;
	SYS_TIME.wDay = Day;
	SYS_TIME.wHour = Hour;
	SYS_TIME.wMinute = Minute;
	SYS_TIME.wSecond = Second;
	SYS_TIME.wMilliseconds = Milliseconds;

	// File Time
	b_Result = SystemTimeToFileTime(&SYS_TIME, &FILE_TIME);
	if (!b_Result) { CloseHandle(hFile); return false; }

	// Set
	b_Result = SetFileTime(hFile, &FILE_TIME, &FILE_TIME, &FILE_TIME);
	if (!b_Result) { CloseHandle(hFile); return false; }

	// Close
	CloseHandle(hFile);

	// Complete
	return b_Result;

#else
	return false;
#endif

}