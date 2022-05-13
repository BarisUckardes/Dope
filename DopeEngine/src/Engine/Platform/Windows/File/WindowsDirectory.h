#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsDirectory
	{
	public:
		WindowsDirectory() = delete;
		~WindowsDirectory() = delete;

		FORCEINLINE static bool create_directory(const String& path);
		FORCEINLINE static bool delete_directory(const String& path);
		FORCEINLINE static bool get_folder_name(const String& path, String& folderNameOut);
		FORCEINLINE static bool get_item_names(const String& path, Array<String>& itemsOut);
		FORCEINLINE static bool get_folder_names(const String& path, Array<String>& foldersOut);
		FORCEINLINE static bool get_file_names(const String& path, Array<String>& filesOut);
		FORCEINLINE static bool get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut);
		FORCEINLINE static bool is_directory_exists(const String& path);
	};


}