#pragma once
#include <Engine/Core/Symbols.h>
#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Core/ConsoleLog.h>
#endif
#define LOG(header,content,...) LOG_IMPL(header,content,__VA_ARGS__);