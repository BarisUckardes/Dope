#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	/// <summary>
	/// Platform agnostic directory operations
	/// </summary>
	class DOPE_ENGINE_API PlatformDirectory
	{
	public:
		PlatformDirectory() = delete;
		~PlatformDirectory() = delete;

		/// <summary>
		/// Creates anew directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool create_directory(const String& path);

		/// <summary>
		/// Deletes the existing directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool delete_directory(const String& path);

		/// <summary>
		/// Returns the
		/// </summary>
		/// <param name="path"></param>
		/// <param name="folderNameOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_folder_name(const String& path, String& folderNameOut);

		/// <summary>
		/// Returns all the folder and file names
		/// </summary>
		/// <param name="path"></param>
		/// <param name="itemsOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_item_names(const String& path, Array<String>& itemsOut);

		/// <summary>
		/// Returns only the folder names 
		/// </summary>
		/// <param name="path"></param>
		/// <param name="foldersOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_folder_names(const String& path, Array<String>& foldersOut);

		/// <summary>
		/// Returns only the file names
		/// </summary>
		/// <param name="path"></param>
		/// <param name="filesOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_file_names(const String& path, Array<String>& filesOut);

		/// <summary>
		/// Returns the files with the specific extension
		/// </summary>
		/// <param name="path"></param>
		/// <param name="extension"></param>
		/// <param name="filesOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut);

		/// <summary>
		/// Returns whether the specified directory exists
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool is_directory_exists(const String& path);
	};
}