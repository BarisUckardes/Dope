#include "PlatformDirectory.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/File/WindowsDirectory.h>
typedef DopeEngine::PlatformDirectory PlatformDirectoryAbstraction;
#endif

namespace DopeEngine
{
    bool PlatformDirectory::create_directory(const String& path)
    {
        return PlatformDirectoryAbstraction::create_directory(path);
    }

    bool PlatformDirectory::delete_directory(const String& path)
    {
        return PlatformDirectoryAbstraction::delete_directory(path);
    }

    bool PlatformDirectory::get_folder_name(const String& path, String& folderNameOut)
    {
        return PlatformDirectoryAbstraction::get_folder_name(path,folderNameOut);
    }

    bool PlatformDirectory::get_item_names(const String& path, Array<String>& itemsOut)
    {
        return PlatformDirectoryAbstraction::get_item_names(path,itemsOut);
    }

    bool PlatformDirectory::get_folder_names(const String& path, Array<String>& foldersOut)
    {
        return PlatformDirectoryAbstraction::get_folder_names(path,foldersOut);
    }

    bool PlatformDirectory::get_file_names(const String& path, Array<String>& filesOut)
    {
        return PlatformDirectoryAbstraction::get_file_names(path,filesOut);
    }

    bool PlatformDirectory::get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut)
    {
        return PlatformDirectoryAbstraction::get_file_names_via_extension(path,extension,filesOut);
    }

    bool PlatformDirectory::is_directory_exists(const String& path)
    {
        return PlatformDirectoryAbstraction::is_directory_exists(path);
    }

}