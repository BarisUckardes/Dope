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

		/// <summary>
		/// Returns whether the file exists or not
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool is_file_exists(const String& path);

		/// <summary>
		/// Creates anew file
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool create_file(const String& path);

		/// <summary>
		/// Deletes the existing file
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool delete_file(const String& path);

		/// <summary>
		/// Writes string to file with the specified offset
		/// </summary>
		/// <param name="path"></param>
		/// <param name="content"></param>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE static bool write(const String& path, const String& content,const unsigned long offset);

		/// <summary>
		/// Writes bytes to file with the specified offset
		/// </summary>
		/// <param name="path"></param>
		/// <param name="block"></param>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE static bool write(const String& path, const ByteBlock& block,const unsigned long offset);

		/// <summary>
		/// Reads file to string with the specified intervals
		/// </summary>
		/// <param name="path"></param>
		/// <param name="contentOut"></param>
		/// <param name="startIndex"></param>
		/// <param name="endIndex"></param>
		/// <returns></returns>
		FORCEINLINE static bool read(const String& path, String& contentOut,const unsigned long startIndex = 0,const unsigned long endIndex = 0);

		/// <summary>
		/// Reads file to bytes with the specified intervals
		/// </summary>
		/// <param name="path"></param>
		/// <param name="block"></param>
		/// <param name="startIndex"></param>
		/// <param name="endIndex"></param>
		/// <returns></returns>
		FORCEINLINE static bool read(const String& path, ByteBlock& block,const unsigned long startIndex = 0,const unsigned long endIndex = 0);

		/// <summary>
		/// Returns the total file length/size
		/// </summary>
		/// <param name="path"></param>
		/// <param name="lengthOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_file_length(const String& path, unsigned long& lengthOut);

		/// <summary>
		/// Returns the file extension
		/// </summary>
		/// <param name="path"></param>
		/// <param name="extensionOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_file_extension(const String& path, String& extensionOut);

		/// <summary>
		/// Extracts the file name out of the given path
		/// </summary>
		/// <param name="path"></param>
		/// <param name="fileNameOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool get_file_name_from_path(const String& path,String& fileNameOut);
	};
}