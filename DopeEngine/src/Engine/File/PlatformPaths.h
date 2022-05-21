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

		/// <summary>
		/// Returns the current executable path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String get_executable_path();

		/// <summary>
		/// Returns the asset domain path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String get_domain_path();

		/// <summary>
		/// Returns the app data/persistent data path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String get_app_data_path(); // persistent data path

		/// <summary>
		/// Returns the program files path (might be Windows only ?? )
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String get_program_files_path();

		/// <summary>
		/// Returns the desktop path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String get_desktop_path();
	};
}