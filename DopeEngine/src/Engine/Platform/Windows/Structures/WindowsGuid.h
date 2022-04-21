#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Basic os-agnostic guid abstraction class
	/// </summary>
	class DOPE_ENGINE_API WindowsGuid final
	{
	public:
		static  WindowsGuid create();
		WindowsGuid(unsigned long a, unsigned short b, unsigned short c, unsigned char d[8]);
		WindowsGuid();
		~WindowsGuid();

		//String get_as_string() const;

		unsigned long A;
		unsigned short B;
		unsigned short C;
		unsigned char D[8];
	};

	DOPE_ENGINE_API bool operator==(const WindowsGuid& a, const WindowsGuid& b);
	DOPE_ENGINE_API bool operator!=(const WindowsGuid& a, const WindowsGuid& b);
}