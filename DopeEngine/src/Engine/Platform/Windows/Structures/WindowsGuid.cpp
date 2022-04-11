#include "WindowsGuid.h"
#include <rpc.h>
#include <stdio.h>
#include <Engine/Memory/Memory.h>
namespace DopeEngine
{
	WindowsGuid WindowsGuid::create()
	{
		WindowsGuid guid;
		CoCreateGuid((GUID*)&guid);
		return guid;
	}
	WindowsGuid::WindowsGuid(unsigned long a, unsigned short b, unsigned short c, unsigned char d[8])
	{
		A = a;
		B = b;
		C = c;
		Memory::memory_copy(&D, &d, 8);
	}
	WindowsGuid::WindowsGuid()
	{
		A = 0;
		B = 0;
		C = 0;
		Memory::memory_set(&D, 0, 8);
	}
	WindowsGuid::~WindowsGuid()
	{

	}
	DOPE_ENGINE_API bool operator==(const WindowsGuid& a, const WindowsGuid& b)
	{
		return
			a.A == b.A &&
			a.B == b.B &&
			a.C == b.C &&
			Memory::memory_check(a.D, b.D, 8);

	}
	DOPE_ENGINE_API bool operator!=(const WindowsGuid& a, const WindowsGuid& b)
	{
		return
			a.A != b.A ||
			a.B != b.B ||
			a.C != b.C ||
			Memory::memory_check(a.D, b.D, 8);
	}
}