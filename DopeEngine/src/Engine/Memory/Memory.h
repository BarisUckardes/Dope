#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/Definitions.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API Memory
	{
	public:
		Memory() = delete;
		~Memory() = delete;

		FORCEINLINE static void memory_copy(void* destination, const void* source, unsigned long byteCount);
		FORCEINLINE static void memory_set(void* destination, Byte value, unsigned long count);
		FORCEINLINE static bool memory_check(const void* a, const void* b, unsigned long count);
	};


}