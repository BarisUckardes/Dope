#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Guid.h>
namespace DopeEngine
{
	/// <summary>
	/// Basic os-agnostic guid abstraction class
	/// </summary>
	class DOPE_ENGINE_API WindowsGuidGenerator final
	{
	public:
		WindowsGuidGenerator() = delete;
		~WindowsGuidGenerator() = delete;

		static void create_guid(Guid& guid);
	};


}