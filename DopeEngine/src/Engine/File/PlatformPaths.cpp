#include "PlatformPaths.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/File/WindowsPaths.h>
typedef DopeEngine::WindowsPaths PlatformPathsAbstraction;
#endif
namespace DopeEngine
{
	String PlatformPaths::get_executable_path()
	{
		return PlatformPathsAbstraction::get_executable_path();
	}

	String PlatformPaths::get_domain_path()
	{
		return PlatformPathsAbstraction::get_domain_path();
	}

	String PlatformPaths::get_app_data_path()
	{
		return PlatformPathsAbstraction::get_app_data_path();
	}

	String PlatformPaths::get_program_files_path()
	{
		return PlatformPathsAbstraction::get_program_files_path();
	}

	String PlatformPaths::get_desktop_path()
	{
		return PlatformPathsAbstraction::get_desktop_path();
	}

}