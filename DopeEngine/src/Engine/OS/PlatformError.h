#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Platform agnostic error util class
	/// </summary>
	class DOPE_ENGINE_API PlatformError
	{
	public:
		PlatformError() = delete;
		~PlatformError() = delete;

		FORCEINLINE static String get_last_platform_error();
	};


}