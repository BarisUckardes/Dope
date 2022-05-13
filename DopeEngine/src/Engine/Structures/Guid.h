#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Basic os-agnostic guid abstraction class
	/// </summary>
	class DOPE_ENGINE_API Guid final
	{
	public:
		Guid(unsigned long a, unsigned short b, unsigned short c, unsigned char d[8]);
		Guid();
		~Guid();


		unsigned long A;
		unsigned short B;
		unsigned short C;
		unsigned char D[8];
	};

	DOPE_ENGINE_API bool operator==(const Guid& a, const Guid& b);
	DOPE_ENGINE_API bool operator!=(const Guid& a, const Guid& b);
}