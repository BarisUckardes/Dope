#include "WindowsMutex.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	WindowsMutex::WindowsMutex()
	{
		create_win32_mutex();
	}
	WindowsMutex::~WindowsMutex()
	{
		delete_win32_mutex();
	}
	void WindowsMutex::lock()
	{
		WaitForSingleObject(Handle, INFINITE);
	}
	void WindowsMutex::unlock()
	{
		ReleaseMutex(Handle);
	}
	void WindowsMutex::create_win32_mutex()
	{
		Handle = CreateMutex(NULL, FALSE, NULL);
		ASSERT(Handle != NULL, "WindowsMutex", "Mutex creation failed!, Something is wrong");
	}
	void WindowsMutex::delete_win32_mutex()
	{
		CloseHandle(Handle);
	}
}