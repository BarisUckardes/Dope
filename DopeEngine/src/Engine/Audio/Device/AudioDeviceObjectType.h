#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	enum class DOPE_ENGINE_API AudioDeviceObjectType
	{
		Undefined = 0,
		Buffer = 1,
		ListenerState = 2,
		SourceState = 3
	};
}