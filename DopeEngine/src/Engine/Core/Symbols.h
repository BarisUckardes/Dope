#pragma once
#ifdef DOPE_ENGINE_BUILD
#define DOPE_ENGINE_API __declspec(dllexport)
#else
#define DOPE_ENGINE_API __declspec(dllimport)
#endif // RUDY_BUILD FOR IMPORT EXPORT DLL

#define DOPE_ENGINE_EXPORT __declspec(dllexport)

#define FORCEINLINE __forceinline