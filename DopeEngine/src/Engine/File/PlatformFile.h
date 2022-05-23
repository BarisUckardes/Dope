#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class ByteBlock;

	/// <summary>
	/// Platform agnostic file operations
	/// </summary>
	class DOPE_ENGINE_API PlatformFile
	{
	public:
		PlatformFile() = delete;
		~PlatformFile() = delete;

		FORCEINLINE static bool is_file_exists(const String& path);
		FORCEINLINE static bool create_file(const String& path);
		FORCEINLINE static bool delete_file(const String& path);
		FORCEINLINE static bool write(const String& path, const String& content,const unsigned long offset);
		FORCEINLINE static bool write(const String& path, const ByteBlock& block,const unsigned long offset);
		FORCEINLINE static bool read(const String& path, String& contentOut,const unsigned long startIndex = 0,const unsigned long endIndex = 0);
		FORCEINLINE static bool read(const String& path, ByteBlock& block,const unsigned long startIndex = 0,const unsigned long endIndex = 0);
		FORCEINLINE static bool get_file_length(const String& path, unsigned long& lengthOut);
		FORCEINLINE static bool get_file_extension(const String& path, String& extensionOut);
		FORCEINLINE static bool get_file_name_from_path(const String& path,String& fileNameOut);
	};
}