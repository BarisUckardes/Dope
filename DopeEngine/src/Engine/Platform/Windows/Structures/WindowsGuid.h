#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	class Guid;
	class DOPE_ENGINE_API WindowsGuid
	{
	public:
		WindowsGuid() = delete;
		~WindowsGuid() = delete;

		static void create_guid(Guid& guid);
	};
}