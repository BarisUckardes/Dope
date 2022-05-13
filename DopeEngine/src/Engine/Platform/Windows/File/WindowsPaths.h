#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsPaths
	{
	public:
		WindowsPaths() = delete;
		~WindowsPaths() = delete;

		FORCEINLINE static String get_executable_path();
		FORCEINLINE static String get_domain_path();
		FORCEINLINE static String get_app_data_path();
		FORCEINLINE static String get_program_files_path();
		FORCEINLINE static String get_desktop_path();
	};


}