#include "WindowsPaths.h"
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <Shlwapi.h>
#include <ShlObj_core.h>
#define SPECIAL_FOLDER_PATH_SIZE 512
namespace DopeEngine
{
	String WindowsPaths::get_executable_path()
	{
		return String();
	}

	String WindowsPaths::get_domain_path()
	{
		return String();
	}

	String WindowsPaths::get_app_data_path()
	{
		char* buffer = new char[SPECIAL_FOLDER_PATH_SIZE];
		SHGetSpecialFolderPathA(NULL, buffer, CSIDL_APPDATA, false);
		return String(buffer);
	}

	String WindowsPaths::get_program_files_path()
	{
		char* buffer = new char[SPECIAL_FOLDER_PATH_SIZE];
		SHGetSpecialFolderPathA(NULL, buffer, CSIDL_PROGRAM_FILES, false);
		return String(buffer);
	}

	String WindowsPaths::get_desktop_path()
	{
		char* buffer = new char[SPECIAL_FOLDER_PATH_SIZE];
		SHGetSpecialFolderPathA(NULL, buffer, CSIDL_DESKTOP, false);
		return String(buffer);
	}

}