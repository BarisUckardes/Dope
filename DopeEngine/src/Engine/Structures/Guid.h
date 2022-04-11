#pragma once
#include <Engine/Core/Symbols.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Structures/WindowsGuid.h>
typedef DopeEngine::WindowsGuid Guid;
#endif