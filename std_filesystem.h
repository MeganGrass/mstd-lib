/*
*
*	Megan Grass
*	January 01, 2024
*
*
*	TODO: 
*		Implement Operations from std::basic_string_view (https://en.cppreference.com/w/cpp/string/basic_string_view)
*
*		Do so many of these functions need to be bool?
*
*		Many of these functions need to be better tested
*
*		Thread safety?
*
*/


#pragma once

#include "std_exception.h"

#include <filesystem>

#include <chrono>
using namespace std::chrono;

#ifdef CreateDirectory
#undef CreateDirectory
#endif

/*
*	https://en.cppreference.com/w/cpp/header/filesystem
*/
class Standard_FileSystem :
	protected Standard_Exception {
private:


protected:


	/*
		Test a filesystem path for presence of a file stem and extension
	*/
	[[nodiscard]] bool TestForFileName(std::filesystem::path _Path);


	/*
		Get an absolute, weakly canonical, and preferred filesystem path with the file stem and extension removed
	*/
	[[nodiscard]] std::filesystem::path CleanDirectoryPath(std::filesystem::path _Path);


public:


	/*
		De/Construction
	*/
	explicit constexpr Standard_FileSystem(void) noexcept = default;
	virtual ~Standard_FileSystem(void) noexcept = default;


	/*
		Get an absolute, weakly canonical, and preferred filesystem path
	*/
	[[nodiscard]] std::filesystem::path CleanPath(std::filesystem::path _Path);


	/*
		Check if a file or directory exists
	*/
	[[nodiscard]] bool Exists(std::filesystem::path _Path);


	/*
		Determine if a filesystem path is a directory
	*/
	[[nodiscard]] bool IsDirectory(std::filesystem::path _Path);


	/*
		Determine if a filesystem path is a regular file
	*/
	[[nodiscard]] bool IsFile(std::filesystem::path _Path);


	/*
		Get a file or directory's size
	*/
	[[nodiscard]] std::uintmax_t FileSize(std::filesystem::path _Path);


	/*
		Resize a file
	*/
	bool ResizeFile(std::filesystem::path _Path, std::uintmax_t _Size);


	/*
		Get a directory filesystem path: absolute, weakly canonical, preferred, file stem and extension removed
	*/
	[[nodiscard]] std::filesystem::path GetDirectory(std::filesystem::path _Path) { return CleanDirectoryPath(_Path); }


	/*
		Create a directory
		If path includes a filename (file stem and extension), it will be ignored
		Return true if the directory already exists or was created
	*/
	bool CreateDirectory(std::filesystem::path _Path);


	/*
		Rename file or directory
	*/
	bool Rename(std::filesystem::path& _Path, std::filesystem::path _NewName, bool bPathMustExist = true);


	/*
		Get the application's current working directory
	*/
	[[nodiscard]] std::filesystem::path GetCurrentWorkingDir(void) { return std::filesystem::current_path(); }


	/*
		Set the application's current working directory
	*/
	bool SetCurrentWorkingDir(std::filesystem::path& _Path, bool bCreateIfDoesntExist = false);


	/*
		Get the system's temporary directory
	*/
	[[nodiscard]] std::filesystem::path GetTempDirectory(void) { return std::filesystem::temp_directory_path(); }


	/*
		Copy file from source to destination
	*/
	bool Copy(std::filesystem::path _Source, std::filesystem::path _Destination, bool bOverwrite = false);


	/*
		Get list of regular files in directory
	*/
	[[nodiscard]] std::vector<std::filesystem::path> GetFileList(std::filesystem::path _Path);


	/*
		Get the file stem and extension from the given filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileName(std::filesystem::path _Path);


	/*
		Set the file stem and extension for the given filesystem path
	*/
	bool SetFileName(std::filesystem::path& _Path, std::filesystem::path _NewName, bool bPathMustExist = true);


	/*
		Get the file stem from the given filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileStem(std::filesystem::path _Path);


	/*
		Get the file extension from the given filesystem path
	*/
	[[nodiscard]] std::filesystem::path GetFileExtension(std::filesystem::path _Path);


	/*
		Set the file extension for the given filesystem path
	*/
	bool SetFileExtension(std::filesystem::path& _Path, std::filesystem::path _NewExt, bool bPathMustExist = true);


	/*
		Set File Date
	 
		Example:
			SetFileDate(Path, sys_days{ 1d / 1 / 2024 } + 12h + 0min + 0s + 123456us);
	*/
	void SetFileDate(std::filesystem::path _Path, std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long long, std::micro>> _FileTime);


	/*
		Set File Date to Now
	*/
	void SetFileDateToNow(std::filesystem::path _Path);


	/*
		Set File Date (Windows Ver.)
	*/
	bool SetFileDateWin(std::filesystem::path _Path, WORD Year, WORD Month, WORD Day, WORD Hour, WORD Minute, WORD Second, WORD Milliseconds);


};