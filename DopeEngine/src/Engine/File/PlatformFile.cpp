#include "PlatformFile.h"
#include <Engine/Memory/ByteBlock.h>


#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/File/WindowsFile.h>
typedef DopeEngine::WindowsFile PlatformFileAbstraction;
#endif

namespace DopeEngine
{
	bool PlatformFile::is_file_exists(const String& path)
	{
		return PlatformFileAbstraction::is_file_exists(path);
	}

	bool PlatformFile::create_file(const String& path)
	{
		return PlatformFileAbstraction::create_file(path);
	}

	bool PlatformFile::delete_file(const String& path)
	{
		return PlatformFileAbstraction::delete_file(path);
	}

	bool PlatformFile::write(const String& path, const String& content, const unsigned long offset)
	{
		return PlatformFileAbstraction::write(path,content,offset);
	}

	bool PlatformFile::write(const String& path, const ByteBlock& block, const unsigned long offset)
	{
		return PlatformFileAbstraction::write(path,block,offset);
	}

	bool PlatformFile::read(const String& path, String& contentOut, const unsigned long startIndex, const unsigned long endIndex)
	{
		return PlatformFileAbstraction::read(path,contentOut,startIndex,endIndex);
	}

	bool PlatformFile::read(const String& path, ByteBlock& block, const unsigned long startIndex, const unsigned long endIndex)
	{
		return PlatformFileAbstraction::read(path,block,startIndex,endIndex);
	}

	bool PlatformFile::get_file_length(const String& path, unsigned long& lengthOut)
	{
		return PlatformFileAbstraction::get_file_length(path,lengthOut);
	}

	bool PlatformFile::get_file_extension(const String& path, String& extensionOut)
	{
		return PlatformFileAbstraction::get_file_extension(path,extensionOut);
	}

	bool PlatformFile::get_file_name_from_path(const String& path, String& fileNameOut)
	{
		return PlatformFileAbstraction::get_file_name_from_path(path,fileNameOut);
	}

}