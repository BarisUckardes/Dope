#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/ConsoleLog.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Core/WindowsAssert.h>
#endif

#define ASSERT(condition,header,message,...) if(!(condition)) { LOG(header,message,__VA_ARGS__) ASSERT_IMPL  }