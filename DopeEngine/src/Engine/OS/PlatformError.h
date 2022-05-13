#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API PlatformError
	{
	public:
		PlatformError() = delete;
		~PlatformError() = delete;

		FORCEINLINE static String get_last_platform_error();
	};


}