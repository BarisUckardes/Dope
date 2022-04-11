#pragma once
#include <Engine/Core/Symbols.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Threading/WindowsMutex.h>
typedef DopeEngine::WindowsMutex Mutex;
#endif
