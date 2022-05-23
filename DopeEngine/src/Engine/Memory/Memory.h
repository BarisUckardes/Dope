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

		static void memory_copy(void* destination, const void* source, unsigned long byteCount);
		static void memory_set(void* destination, Byte value, unsigned long count);
		static bool memory_check(const void* a, const void* b, unsigned long count);
	};


}