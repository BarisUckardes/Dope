#include "Guid.h"
#include <Engine/Memory/Memory.h>
#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Structures/WindowsGuid.h>
typedef DopeEngine::WindowsGuid GuidAbstraction;
#endif
namespace DopeEngine
{
	Guid Guid::create()
	{
		/*
		* Create default guid
		*/
		Guid id;

		/*
		* Call impl
		*/
		GuidAbstraction::create_guid(id);

		return id;

	}
	Guid::Guid(unsigned long a, unsigned short b, unsigned short c, unsigned char d[8])
	{
		A = a;
		B = b;
		C = c;
		Memory::memory_copy(&D, &d, 8);
	}
	Guid::Guid()
	{
		A = 0;
		B = 0;
		C = 0;
		Memory::memory_set(&D,0, 8);
	}
	Guid::~Guid()
	{

	}
	DOPE_ENGINE_API bool operator==(const Guid& a, const Guid& b)
	{
		return
			a.A == b.A &&
			a.B == b.B &&
			a.C == b.C &&
			Memory::memory_check(a.D, b.D, 8);

	}
	DOPE_ENGINE_API bool operator!=(const Guid& a, const Guid& b)
	{
		return
			a.A != b.A ||
			a.B != b.B ||
			a.C != b.C ||
			Memory::memory_check(a.D, b.D, 8);
	}
}