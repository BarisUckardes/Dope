#pragma once
#include <Engine/Core/Symbols.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Threading/WindowsThread.h>
typedef DopeEngine::WindowsThread Thread;
#endif