#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/Definitions.h>

namespace DopeEngine
{
	/// <summary>
	/// Util Memory operations
	/// </summary>
	class DOPE_ENGINE_API Memory
	{
	public:
		Memory() = delete;
		~Memory() = delete;

		/// <summary>
		/// Copies the source data with specified length to destination
		/// </summary>
		/// <param name="destination"></param>
		/// <param name="source"></param>
		/// <param name="byteCount"></param>
		static void memory_copy(void* destination, const void* source, unsigned long byteCount);

		/// <summary>
		/// Sets the destination with the specified byte value with a count
		/// </summary>
		/// <param name="destination"></param>
		/// <param name="value"></param>
		/// <param name="count"></param>
		static void memory_set(void* destination, Byte value, unsigned long count);

		/// <summary>
		/// Validates if the given two addresses are equal with respect to count
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		static bool memory_check(const void* a, const void* b, unsigned long count);
	};


}