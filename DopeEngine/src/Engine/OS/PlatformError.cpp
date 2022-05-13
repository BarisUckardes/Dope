#include "PlatformError.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Error/WindowsError.h>
typedef DopeEngine::WindowsError PlatformErrorAbstraction;
#endif

namespace DopeEngine
{
	String PlatformError::get_last_platform_error()
	{
		return PlatformErrorAbstraction::get_last_error();
	}

}