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
		const DWORD diagnostic = GetFileAttributesA(*path);
		if (diagnostic == INVALID_FILE_ATTRIBUTES || diagnostic == FILE_ATTRIBUTE_DIRECTORY)
			return false;

		return true;
	}

	bool WindowsFile::create_file(const String& path)
	{
		const bool fileExists = is_file_exists(path);
		if (fileExists) // try delete file
		{
			delete_file(path);
		}

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

		if (fileHandle)
			CloseHandle(fileHandle);

		return fileHandle != nullptr;
	}

	bool WindowsFile::delete_file(const String& path)
	{
		if (is_file_exists(*path))
			return DeleteFileA(*path);
	}

	bool WindowsFile::write(const String& path, const String& content, const unsigned long offset)
	{
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

		unsigned long writtenBytes = 0;

		const bool writeSuccess = WriteFile(fileHandle, content.get_source(), content.get_cursor(), &writtenBytes, NULL);
		if (!writeSuccess)
			return false;

		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::write(const String& path, const ByteBlock& block, const unsigned long offset)
	{
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

		unsigned long writtenBytes = 0;

		const bool writeSuccess = WriteFile(fileHandle, block.get_block_data_ptr(), block.get_size(), &writtenBytes, NULL);
		if (!writeSuccess)
			return false;

		CloseHandle(fileHandle);
	}

	bool WindowsFile::read(const String& path, String& contentOut, const unsigned long startIndex, const unsigned long endIndex)
	{
		if (!is_file_exists(path))
			return false;

		unsigned long fileSize = 0;
		get_file_length(path, fileSize);

		const unsigned long expectedReadInterval = endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		if (!fileHandle)
			return false;

		Byte* readBuffer = new Byte[expectedReadInterval];
		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData,FileIOCompletionRoutine);

		if (!readSuccess)
			return false;

		contentOut = String((char*)readBuffer, expectedReadInterval);

		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::read(const String& path, ByteBlock& block, const unsigned long startIndex, const unsigned long endIndex)
	{
		if (!is_file_exists(path))
			return false;

		unsigned long fileSize = 0;
		get_file_length(path, fileSize);

		const unsigned long expectedReadInterval = endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		if (!fileHandle)
			return false;

		Byte* readBuffer = new Byte[expectedReadInterval];

		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData, FileIOCompletionRoutine);
		if (!readSuccess)
			return false;

		block = ByteBlock(readBuffer, expectedReadInterval);

		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::get_file_length(const String& path, unsigned long& lengthOut)
	{
		const HANDLE fileHandle = CreateFileA(*path,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (!fileHandle)
			return false;

		lengthOut = GetFileSize(fileHandle, NULL);

		CloseHandle(fileHandle);

		return true;
	}

	bool WindowsFile::get_file_extension(const String& path, String& extensionOut)
	{
		if (!is_file_exists(path))
			return false;

		extensionOut = PathFindExtensionA(*path);

		return false;
	}

	bool WindowsFile::get_file_name_from_path(const String& path, String& fileNameOut)
	{
		return PathFindFileNameA(*path);
	}

}