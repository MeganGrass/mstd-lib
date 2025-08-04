/*
*
*	Megan Grass
*	January 01, 2024
*
*/


#include "std_common.h"

#include <mutex>

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Ole32.lib")


void Standard_Windows_Common::GetErrorMessage(bool b_ExitProcess, const std::source_location Location)
{
	wchar_t* lpBuffer = nullptr;

	DWORD dwMessageId = GetLastError();

	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		0,
		dwMessageId,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpBuffer,
		0,
		0);

	std::string ErrorStr = FormatCStyle("\r\nError Code: %d\r\n\r\n%ws\r\nFile: %s\r\nFunction: \'%s\'\r\nLine: \'%d\'\r\n\r\n", dwMessageId, lpBuffer, Location.file_name(), Location.function_name(), Location.line());

	std::string CallStackStr = Standard_Exception::FormatString("Call Stack:\r\n{}\r\n\r\n", std::stacktrace::current());

	ErrorStr += CallStackStr;

	std::filesystem::path CheatStr = ErrorStr;

	OutputDebugStringW(CheatStr.wstring().c_str());

	TaskDialog(hWndOwner, hInstance, L"GetLastError", 0, CheatStr.wstring().c_str(), TDCBF_OK_BUTTON, 0, 0);

	if (b_ExitProcess) { ExitProcess(dwMessageId); }
}

const std::filesystem::path Standard_Windows_Common::GetModuleStr(void)
{
	std::vector <wchar_t> _Filename(65535);
	GetModuleFileNameW(0, _Filename.data(), static_cast<DWORD>(_Filename.size()));
	return _Filename.data();
}

const std::filesystem::path Standard_Windows_Common::GetModuleDir(void)
{
	std::vector <wchar_t> _Filename(65535);
	GetModuleFileNameW(0, _Filename.data(), static_cast<DWORD>(_Filename.size()));
	return GetDirectory(_Filename.data());
}

const std::filesystem::path Standard_Windows_Common::GetUserDir(void)
{
	std::filesystem::path UserPath;
	wchar_t* _Path = (wchar_t*)CoTaskMemAlloc(65535);
	if (SHGetKnownFolderPath(FOLDERID_Profile, 0, 0, &_Path) == S_OK) { UserPath = GetDirectory(_Path); }
	else { UserPath = L""; }
	CoTaskMemFree(_Path);
	return UserPath;
}

const std::filesystem::path Standard_Windows_Common::GetUserDocumentsDir(void)
{
	std::filesystem::path UserPath;
	wchar_t* _Path = (wchar_t*)CoTaskMemAlloc(65535);
	if (SHGetKnownFolderPath(FOLDERID_Documents, 0, 0, &_Path) == S_OK) { UserPath = GetDirectory(_Path); }
	else { UserPath = L""; }
	CoTaskMemFree(_Path);
	return UserPath;
}

const std::filesystem::path Standard_Windows_Common::GetUserSavedGamesDir(void)
{
	std::filesystem::path UserPath;
	wchar_t* _Path = (wchar_t*)CoTaskMemAlloc(65535);
	if (SHGetKnownFolderPath(FOLDERID_SavedGames, 0, 0, &_Path) == S_OK) { UserPath = GetDirectory(_Path); }
	else { UserPath = L""; }
	CoTaskMemFree(_Path);
	return UserPath;
}

const std::vector<std::filesystem::path> Standard_Windows_Common::GetFonts(void)
{
	std::vector<std::filesystem::path> Fonts;
	for (const auto& Entry : std::filesystem::directory_iterator(L"C:\\Windows\\Fonts\\"))
	{
		if (Entry.is_regular_file())
		{
			StringW Extension = Entry.path().extension().wstring();
			if (ToUpper(Extension) == L".TTF")
			{
				Fonts.push_back(Entry.path());
			}
		}
	}
	return Fonts;
}

const std::optional<std::filesystem::path> Standard_Windows_Common::GetOpenFilename(StrVecW _Description, StrVecW _Filter)
{
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

	// Error
	if (_Description.size() != _Filter.size()) { return std::nullopt; }

	// CoCreate
	IFileDialog* pFileDialog;
	if (CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog)) != S_OK) { return std::nullopt; }

	// Options
	DWORD dwFlags;
	if (pFileDialog->GetOptions(&dwFlags) != S_OK) { return std::nullopt; }
	if (pFileDialog->SetOptions(FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR | FOS_FILEMUSTEXIST | FOS_OKBUTTONNEEDSINTERACTION | FOS_DONTADDTORECENT) != S_OK) { return std::nullopt; }

	// File Types
	std::vector<COMDLG_FILTERSPEC> FilterSpec(_Description.size());
	for (auto& FileTypes : FilterSpec)
	{
		FileTypes.pszName = _Description[&FileTypes - &FilterSpec[0]].c_str();
		FileTypes.pszSpec = _Filter[&FileTypes - &FilterSpec[0]].c_str();
	}
	pFileDialog->SetFileTypes((UINT)FilterSpec.size(), FilterSpec.data());

	// Default
	CleanString(_Filter[0], { L"*", L"." });
	if (pFileDialog->SetFileTypeIndex(1) != S_OK) { return std::nullopt; }
	if (pFileDialog->SetDefaultExtension(_Filter[0].c_str()) != S_OK) { return std::nullopt; }

	// Show
	if (pFileDialog->Show(hWndOwner) != S_OK) { return std::nullopt; }

	// Result
	IShellItem* pShellItem;
	if (pFileDialog->GetResult(&pShellItem) != S_OK) { return std::nullopt; }

	// Path
	LPWSTR Name;
	if (pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &Name) != S_OK) { return std::nullopt; }

	// Buffer
	std::filesystem::path Path = Name;

	// Cleanup
	CoTaskMemFree(Name);
	pShellItem->Release();
	pFileDialog->Release();

	// Complete
	return Path;
}

const std::optional<std::filesystem::path> Standard_Windows_Common::GetSaveFilename(StrVecW _Description, StrVecW _Filter)
{
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

	// Error
	if (_Description.size() != _Filter.size()) { return std::nullopt; }

	// CoCreate
	IFileDialog* pFileDialog;
	if (CoCreateInstance(CLSID_FileSaveDialog, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog)) != S_OK) { return std::nullopt; }

	// Options
	DWORD dwFlags;
	if (pFileDialog->GetOptions(&dwFlags) != S_OK) { return std::nullopt; }
	if (pFileDialog->SetOptions(FOS_FORCEFILESYSTEM | FOS_STRICTFILETYPES | FOS_NOCHANGEDIR | FOS_PATHMUSTEXIST | FOS_OVERWRITEPROMPT | FOS_OKBUTTONNEEDSINTERACTION | FOS_DONTADDTORECENT) != S_OK) { return std::nullopt; }

	// File Types
	std::vector<COMDLG_FILTERSPEC> FilterSpec(_Description.size());
	for (auto& FileTypes : FilterSpec)
	{
		FileTypes.pszName = _Description[&FileTypes - &FilterSpec[0]].c_str();
		FileTypes.pszSpec = _Filter[&FileTypes - &FilterSpec[0]].c_str();
	}
	pFileDialog->SetFileTypes((UINT)FilterSpec.size(), FilterSpec.data());

	// Default
	CleanString(_Filter[0], { L"*", L"." });
	if (pFileDialog->SetFileTypeIndex(1) != S_OK) { return std::nullopt; }
	if (pFileDialog->SetDefaultExtension(_Filter[0].c_str()) != S_OK) { return std::nullopt; }

	// Show
	if (pFileDialog->Show(hWndOwner) != S_OK) { return std::nullopt; }

	// Result
	IShellItem* pShellItem;
	if (pFileDialog->GetResult(&pShellItem) != S_OK) { return std::nullopt; }

	// Path
	LPWSTR Name;
	if (pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &Name) != S_OK) { return std::nullopt; }

	// Buffer
	std::filesystem::path Path = Name;

	// Cleanup
	CoTaskMemFree(Name);
	pShellItem->Release();
	pFileDialog->Release();

	// Complete
	return Path;
}

[[nodiscard]] const std::optional<std::filesystem::path> Standard_Windows_Common::GetFileDirectory(void) const
{
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

	// CoCreate
	IFileDialog* pFileDialog;
	if (CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog)) != S_OK) { return std::nullopt; }

	// Options
	DWORD dwFlags;
	if (pFileDialog->GetOptions(&dwFlags) != S_OK) { return std::nullopt; }
	if (pFileDialog->SetOptions(FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR | FOS_DONTADDTORECENT) != S_OK) { return std::nullopt; }

	// Show
	if (pFileDialog->Show(hWndOwner) != S_OK) { return std::nullopt; }

	// Result
	IShellItem* pShellItem;
	if (pFileDialog->GetResult(&pShellItem) != S_OK) { return std::nullopt; }

	// Path
	LPWSTR Name;
	if (pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &Name) != S_OK) { return std::nullopt; }

	// Buffer
	std::filesystem::path Path = Name;

	// Cleanup
	CoTaskMemFree(Name);
	pShellItem->Release();
	pFileDialog->Release();

	// Complete
	return Path;
}

const bool Standard_Windows_Common::Question(const std::wstring _Question, ...) const
{
	std::va_list _ArgList;
	va_start(_ArgList, _Question);
	int _StrLen = (std::vswprintf(0, 0, _Question.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Question.c_str(), _ArgList);
	va_end(_ArgList);

	INT Result = 0;

	TaskDialog(hWndOwner, hInstance, L"Question", 0, String.data(), TDCBF_YES_BUTTON | TDCBF_NO_BUTTON, 0, &Result);

	switch (Result)
	{
	case IDNO:
		return false;
	case IDYES:
		return true;
	}

	return false;
}

void Standard_Windows_Common::Message(const std::string _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vsnprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(char));
	std::vector<char> String(_StrLen);
	std::vsnprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	std::wstring WideStr = std::wstring(String.begin(), String.end());

	MessageModal(L"Message", L"", WideStr.data());
}

void Standard_Windows_Common::Message(const std::wstring _Format, ...)
{
	std::va_list _ArgList;
	va_start(_ArgList, _Format);
	int _StrLen = (std::vswprintf(0, 0, _Format.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> String(_StrLen);
	std::vswprintf(String.data(), _StrLen, _Format.c_str(), _ArgList);
	va_end(_ArgList);

	MessageModal(L"Message", L"", String.data());
}

HRESULT CALLBACK Standard_Windows_Common::MessageModalCallbackProc(HWND hWnd, UINT uNotification, WPARAM wParam, LPARAM lParam, LONG_PTR dwRefData)
{
	if (uNotification == TDN_HYPERLINK_CLICKED)
	{
		ShellExecuteW(nullptr, L"open", (LPCWSTR)lParam, nullptr, nullptr, SW_SHOWNORMAL);
	}
	return S_OK;
}

void Standard_Windows_Common::MessageModal(const std::wstring& Title, const std::wstring& MainInstruction, const std::wstring _Content, ...) const
{
	std::va_list _ArgList;
	va_start(_ArgList, _Content);
	int _StrLen = (std::vswprintf(0, 0, _Content.c_str(), _ArgList) + sizeof(wchar_t));
	std::vector<wchar_t> Content(_StrLen);
	std::vswprintf(Content.data(), _StrLen, _Content.c_str(), _ArgList);
	va_end(_ArgList);

	TASKDIALOGCONFIG DialogConfig = { sizeof(TASKDIALOGCONFIG) };
	DialogConfig.hwndParent = hWndOwner;
	DialogConfig.hInstance = hInstance;
	DialogConfig.dwFlags = TDF_ENABLE_HYPERLINKS;
	DialogConfig.pszWindowTitle = Title.c_str();
	DialogConfig.pszMainInstruction = MainInstruction.c_str();
	DialogConfig.pszContent = Content.data();
	DialogConfig.pfCallback = MessageModalCallbackProc;

	TaskDialogIndirect(&DialogConfig, nullptr, nullptr, nullptr);
}