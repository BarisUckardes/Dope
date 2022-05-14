#include "WindowsFile.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <Engine/Memory/ByteBlock.h>
namespace DopeEngine
{
	unsigned long g_TransferredBytes;
	VOID CALLBACK FileIOCompletionRoutine(
		__in  DWORD dwErrorCode,
		__in  DWORD dwNumberOfBytesTransfered,
		__in  LPOVERLAPPED lpOverlapped
	);
	VOID CALLBACK FileIOCompletionRoutine(
		__in  DWORD dwErrorCode,
		__in  DWORD dwNumberOfBytesTransfered,
		__in  LPOVERLAPPED lpOverlapped)
	{
		g_TransferredBytes = dwNumberOfBytesTransfered;
	}
	bool WindowsFile::is_file_exists(const String& path)
	{
		/*
		* Get file diagnostics
		*/
		const DWORD diagnostic = GetFileAttributesA(*path);

		/*
		* Validate
		*/
		if (diagnostic == INVALID_FILE_ATTRIBUTES || diagnostic == FILE_ATTRIBUTE_DIRECTORY)
			return false;

		return true;
	}

	bool WindowsFile::create_file(const String& path)
	{
		/*
		* Check if file exist
		*/
		const bool fileExists = is_file_exists(path);

		/*
		* Validate file existence
		*/
		if (fileExists) // try delete file
		{
			delete_file(path);
		}

		/*
		* Create file and return a file handle
		*/
		const HANDLE fileHandle = CreateFileA(*path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

		/*
		* Validate file handle
		*/
		if (fileHandle)
			CloseHandle(fileHandle);

		return fileHandle != nullptr;
	}

	bool WindowsFile::delete_file(const String& path)
	{
		/*
		* Validate file path
		*/
		if (is_file_exists(*path))
			return DeleteFileA(*path);
	}

	bool WindowsFile::write(const String& path, const String& content, const unsigned long offset)
	{
		/*
		* Validate file
		*/
		HANDLE fileHandle = NULL;
		if (is_file_exists(path)) // overwrite
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}
		else // create new file and write
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}

		/*
		* Write file
		*/
		unsigned long writtenBytes = 0;
		const bool writeSuccess = WriteFile(fileHandle, content.get_source(), content.get_cursor(), &writtenBytes, NULL);

		/*
		* Validate handle
		*/
		if (!writeSuccess)
			return false;

		/*
		* Close file handle
		*/
		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::write(const String& path, const ByteBlock& block, const unsigned long offset)
	{
		/*
		* Validate file
		*/
		HANDLE fileHandle = NULL;
		if (is_file_exists(path)) // overwrite
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}
		else // create new file and write
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}

		/*
		* Write file
		*/
		unsigned long writtenBytes = 0;
		const bool writeSuccess = WriteFile(fileHandle, block.get_block_data_ptr(), block.get_size(), &writtenBytes, NULL);

		/*
		* Validate handle
		*/
		if (!writeSuccess)
			return false;

		/*
		* Close file handle
		*/
		CloseHandle(fileHandle);

	}

	bool WindowsFile::read(const String& path, String& contentOut, const unsigned long startIndex, const unsigned long endIndex)
	{
		/*
		* Validate if file exists
		*/
		if (!is_file_exists(path))
			return false;

		/*
		* Get file length
		*/
		unsigned long fileSize = 0;
		get_file_length(path, fileSize);

		/*
		* Validate file size
		*/
		const unsigned long expectedReadInterval = endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		/*
		* Initialize
		*/
		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		/*
		* Open file for reading
		*/
		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

		/*
		* Validate file handle
		*/
		if (!fileHandle)
			return false;

		/*
		* Read file
		*/
		Byte* readBuffer = new Byte[expectedReadInterval];
		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData,FileIOCompletionRoutine);

		/*
		* Validate read success
		*/
		if (!readSuccess)
			return false;

		/*
		* Set content
		*/
		contentOut = String((char*)readBuffer, expectedReadInterval);

		/*
		* Close handle
		*/
		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::read(const String& path, ByteBlock& block, const unsigned long startIndex, const unsigned long endIndex)
	{
		/*
		* Validate if file exists
		*/
		if (!is_file_exists(path))
			return false;

		/*
		* Get file length
		*/
		unsigned long fileSize = 0;
		get_file_length(path, fileSize);

		/*
		* Validate file size
		*/
		const unsigned long expectedReadInterval = endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		/*
		* Initialize
		*/
		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		/*
		* Open file for reading
		*/
		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

		/*
		* Validate file handle
		*/
		if (!fileHandle)
			return false;

		/*
		* Read file
		*/
		Byte* readBuffer = new Byte[expectedReadInterval];
		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData, FileIOCompletionRoutine);

		/*
		* Validate read success
		*/
		if (!readSuccess)
			return false;

		/*
		* Set content
		*/
		block = ByteBlock(readBuffer, expectedReadInterval);

		/*
		* Close handle
		*/
		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::get_file_length(const String& path, unsigned long& lengthOut)
	{
		/*
		* Create file handle
		*/
		const HANDLE fileHandle = CreateFileA(*path,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);

		/*
		* Validate file handle
		*/
		if (!fileHandle)
			return false;

		/*
		* Get file size
		*/
		lengthOut = GetFileSize(fileHandle, NULL);

		/*
		* Close handle
		*/
		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::get_file_extension(const String& path, String& extensionOut)
	{
		/*
		* Validate file existence
		*/
		if (!is_file_exists(path))
			return false;

		/*
		* Find extension
		*/
		extensionOut = PathFindExtensionA(*path);

		return false;
	}

	bool WindowsFile::get_file_name_from_path(const String& path, String& fileNameOut)
	{
		return PathFindFileNameA(*path);
	}

}