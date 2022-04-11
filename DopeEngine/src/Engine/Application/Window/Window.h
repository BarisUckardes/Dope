#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Event/Delegate.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
typedef DopeEngine::WindowsWindow Window;
#endif