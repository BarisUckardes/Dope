#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsError
	{
	public:
		WindowsError() = delete;
		~WindowsError() = delete;

		FORCEINLINE static String get_last_error();
	};
}