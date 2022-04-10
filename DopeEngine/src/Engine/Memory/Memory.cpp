#include "Memory.h"

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
	void Memory::memory_set(void* destination, Byte value, unsigned long count)
	{
		/*
		* Convert destination to byte
		*/
		Byte* bDestination = (Byte*)destination;

		/*
		* Memset
		*/
		for (unsigned long i = 0; i < count; i++)
		{
			bDestination[i] = value;
		}
	}
	bool Memory::memory_check(const void* a, const void* b, unsigned long count)
	{
		/*
		* Convert to byte
		*/
		const Byte* aByte = (const Byte*)a;
		const Byte* bByte = (const Byte*)b;

		/*
		* Memcheck
		*/
		for (unsigned long i = 0; i < count; i++)
		{
			if (aByte[i] != bByte[i])
				return false;
		}
		return true;
	}
}