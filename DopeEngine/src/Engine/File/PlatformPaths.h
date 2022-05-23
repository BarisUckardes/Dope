#pragma once
#include <Engine/Structures/String.h>


namespace DopeEngine
{
	/// <summary>
	/// Platform agnostic special path operations
	/// </summary>
	class DOPE_ENGINE_API PlatformPaths
	{
	public:
		PlatformPaths() = delete;
		~PlatformPaths() = delete;

		FORCEINLINE static String get_executable_path();
		FORCEINLINE static String get_domain_path();
		FORCEINLINE static String get_app_data_path(); // persistent data path
		FORCEINLINE static String get_program_files_path();
		FORCEINLINE static String get_desktop_path();
	};
}