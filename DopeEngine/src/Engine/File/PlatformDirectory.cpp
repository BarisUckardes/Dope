#include "PlatformDirectory.h"


namespace DopeEngine
{
    bool PlatformDirectory::create_directory(const String& path)
    {
        return false;
    }

    bool PlatformDirectory::delete_directory(const String& path)
    {
        return false;
    }

    bool PlatformDirectory::get_folder_name(const String& path, String& folderNameOut)
    {
        return false;
    }

    bool PlatformDirectory::get_item_names(const String& path, Array<String>& itemsOut)
    {
        return false;
    }

    bool PlatformDirectory::get_folder_names(const String& path, Array<String>& foldersOut)
    {
        return false;
    }

    bool PlatformDirectory::get_file_names(const String& path, Array<String>& filesOut)
    {
        return false;
    }

    bool PlatformDirectory::get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut)
    {
        return false;
    }

    bool PlatformDirectory::is_directory_exists(const String& path)
    {
        return false;
    }

}