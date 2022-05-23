#include "Memory.h"

namespace DopeEngine
{
	void Memory::memory_copy(void* destination, const void* source, unsigned long byteCount)
	{
		const Byte* bSource = (const Byte*)source;
		Byte* bDestination = (Byte*)destination;

		for (unsigned long i = 0; i < byteCount; i++)
		{
			bDestination[i] = bSource[i];
		}
	}
	void Memory::memory_set(void* destination, Byte value, unsigned long count)
	{
		Byte* bDestination = (Byte*)destination;

		for (unsigned long i = 0; i < count; i++)
		{
			bDestination[i] = value;
		}
	}
	bool Memory::memory_check(const void* a, const void* b, unsigned long count)
	{
		const Byte* aByte = (const Byte*)a;
		const Byte* bByte = (const Byte*)b;

		for (unsigned long i = 0; i < count; i++)
		{
			if (aByte[i] != bByte[i])
				return false;
		}
		return true;
	}
}