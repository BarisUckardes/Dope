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
        /*
        * Validate existing directory
        */
        if (is_directory_exists(path))
            return false;

        /*
        * Create directory
        */
        CreateDirectoryA(*path, NULL);
    }

    bool WindowsDirectory::delete_directory(const String& path)
    {
        /*
        * Validate path
        */
        if (!is_directory_exists(path))
            return false;

        /*
        * Get sub items
        */
        Array<String> subItems;
        get_file_names(path, subItems);

        /*
        * Validate sub items
        */
        if (subItems.get_cursor() > 0)
        {
            RemoveDirectoryA(*path);
            return true;
        }

        /*
        * Iterate and sub items
        */
        for (unsigned int i = 0; i < subItems.get_cursor(); i++)
        {
            /*
            * Get item path
            */
            const String itemPath = subItems[i];

            /*
            * Validate if its a file
            */
            const bool bFile = is_directory_exists(itemPath);

            /*
            * Execute proper action
            */
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
        /*
        * Validate folder
        */
        if (!is_directory_exists(path))
            return false;

        /*
        * Get folder name
        */
        folderNameOut = PathFindFileNameA(*path);

        return true;
    }

    bool WindowsDirectory::get_item_names(const String& path, Array<String>& itemsOut)
    {
        /*
       * Create search filter
       */
        const String searchFilter = path + "*";

        /*
        * Create find file
        */
        WIN32_FIND_DATAA fileFindData = { 0 };
        const HANDLE fileHandle = FindFirstFileA(*searchFilter, &fileFindData);

        /*
        * Validate file handle
        */
        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            FindClose(fileHandle);
            return false;
        }

        /*
        * Get file names
        */
        do
        {
            /*
            * Get name
            */
            const String folderName = fileFindData.cFileName;

            /*
            * Reject "." and ".."
            */
            if (folderName == "." || folderName == "..")
                continue;

            /*
            * Register folder name
            */
            itemsOut.add(path + folderName);

        } while (FindNextFileA(fileHandle, &fileFindData));

        return true;
    }

    bool WindowsDirectory::get_folder_names(const String& path, Array<String>& foldersOut)
    {
        /*
        * Validate path
        */
        if (!is_directory_exists(path))
            return false;

        /*
        * Get all file names
        */
        Array<String> items;
        get_file_names(path, items);

        /*
        * Collect the folders
        */
        for (unsigned int i = 0; i < items.get_cursor(); i++)
        {
            /*
            * Validate folder
            */
            if (is_directory_exists(items[i]))
            {
                foldersOut.add(items[i]);
            }
        }

        return true;
    }

    bool WindowsDirectory::get_file_names(const String& path, Array<String>& filesOut)
    {
        /*
        * Validate path
        */
        if (!is_directory_exists(path))
            return false;

        /*
        * Get all file names
        */
        Array<String> items;
        get_file_names(path, items);

        /*
        * Collect the folders
        */
        for (unsigned int i = 0; i < items.get_cursor(); i++)
        {
            /*
            * Validate folder
            */
            if (!is_directory_exists(items[i]))
            {
                filesOut.add(items[i]);
            }
        }

        return true;
    }

    bool WindowsDirectory::get_file_names_via_extension(const String& path, const String& extension, Array<String>& filesOut)
    {
        /*
        * Validate path
        */
        if (!is_directory_exists(path))
            return false;

        /*
        * Get all files
        */
        Array<String> files;
        get_file_names(path,files);

        /*
        * Collect the ones with the extension
        */
        for (unsigned int i = 0; i < files.get_cursor(); i++)
        {
            /*
            * Get file
            */
            const String file = files[i];

            /*
            * Validate if folder
            */
            if (!is_directory_exists(file))
                continue;

            /*
            * Get extension
            */
            String fileExtension;
            PlatformFile::get_file_extension(file, fileExtension);

            /*
            * Validate extension match
            */
            if (fileExtension == extension)
                filesOut.add(file);
        }
    }

    bool WindowsDirectory::is_directory_exists(const String& path)
    {
        /*
        * Get file diagnostics
        */
        const DWORD diagnostic = GetFileAttributesA(*path);

        /*
        * Validate diagnostics
        */
        if (diagnostic != INVALID_FILE_ATTRIBUTES && diagnostic == FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }

}