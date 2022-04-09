#include "Memory.h"
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	void Memory::memory_copy(void* destination, const void* source, unsigned long byteCount)
	{
		/*
		* Convert source and destination
		*/
		const Byte* bSource = (const Byte*)source;
		Byte* bDestination = (Byte*)destination;

		/*
		* Copy
		*/
		for (unsigned long i = 0; i < byteCount; i++)
		{
			bDestination[i] = bSource[i];
		}
	}
}