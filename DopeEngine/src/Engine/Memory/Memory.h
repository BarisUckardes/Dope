#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API Memory
	{
	public:
		Memory() = delete;
		~Memory() = delete;

		FORCEINLINE static void memory_copy(void* destination, const void* source, unsigned long byteCount);
	};


}