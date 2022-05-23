#include "WindowsDirectory.h"
#include <comdef.h>
#include <Windows.h>
#include <mbstring.h>
#include <memory>
#include <string>
#include <system_error>
#include <Shlwapi.h>
#include <Engine/File/PlatformFile.h>
namespace DopeEngine
{
    bool WindowsDirectory::create_directory(const String& path)
    {
        if (is_directory_exists(path))
            return false;

        CreateDirectoryA(*path, NULL);
    }

    bool WindowsDirectory::delete_directory(const String& path)
    {
        if (!is_directory_exists(path))
            return false;

        Array<String> subItems;
        get_file_names(path, subItems);

        if (subItems.get_cursor() > 0)
        {
            RemoveDirectoryA(*path);
            return true;
        }

        for (unsigned int i = 0; i < subItems.get_cursor(); i++)
        {
            const String itemPath = subItems[i];

            const bool bFile = is_directory_exists(itemPath);
            if (bFile)
            {
                PlatformFile::delete_file(itemPath);
            }
            else
            {
                delete_directory(itemPath);
            }
        }
        
        return true;
    }

    bool WindowsDirectory::get_folder_name(const String& path, String& folderNameOut)
    {
        if (!is_directory_exists(path))
            return false;

        folderNameOut = PathFindFileNameA(*path);

        return true;
    }

    bool WindowsDirectory::get_item_names(const String& path, Array<String>& itemsOut)
    {
        const String searchFilter = path + "*";

        WIN32_FIND_DATAA fileFindData = { 0 };

        const HANDLE fileHandle = FindFirstFileA(*searchFilter, &fileFindData);
        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            FindClose(fileHandle);
            return false;
        }
        do
        {

            const String folderName = fileFindData.cFileName;
            if (folderName == "." || folderName == "..")
                continue;

            itemsOut.add(path + folderName);

        } while (FindNextFileA(fileHandle, &fileFindData));

        return true;
    }

    bool WindowsDirectory::get_folder_names(const String& path, Array<String>& foldersOut)
    {
        if (!is_directory_exists(path))
            return false;

        Array<String> items;
        get_file_names(path, items);

        for (unsigned int i = 0; i < items.get_cursor(); i++)
        {
            if (is_directory_exists(items[i]))
            {
                foldersOut.add(items[i]);
            }
        }

        return true;
    }

    bool WindowsDirectory::get_file_names(const String& path, Array<String>& filesOut)
    {
        if (!is_directory_exists(path))
            return false;

        Array<String> items;
        get_file_names(path, items);

        for (unsigned int i = 0; i < items.get_cursor(); i++)
        {
            if (!is_directory_exists(items[i]))
            {
                filesOut.add(items[i]);
            }
        }

        return true;
    }

    bool WindowsDirectory::get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut)
    {
        if (!is_directory_exists(path))
            return false;

        Array<String> files;
        get_file_names(path,files);

        for (unsigned int i = 0; i < files.get_cursor(); i++)
        {
            const String file = files[i];
            if (!is_directory_exists(file))
                continue;

            String fileExtension;
            PlatformFile::get_file_extension(file, fileExtension);

            if (fileExtension == extension)
                filesOut.add(file);
        }
    }

    bool WindowsDirectory::is_directory_exists(const String& path)
    {
        const DWORD diagnostic = GetFileAttributesA(*path);
        if (diagnostic != INVALID_FILE_ATTRIBUTES && diagnostic == FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }

}