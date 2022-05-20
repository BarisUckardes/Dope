#pragma once

#ifdef DOPE_EDITOR_BUILD
#define DOPE_EDITOR_API __declspec(dllexport)
#else
#define DOPE_EDITOR_API __declspec(dllimport)
#endif

#define FORCEINLINE __forceinline