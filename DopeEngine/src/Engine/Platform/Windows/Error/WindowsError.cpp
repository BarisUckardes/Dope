#include "WindowsError.h"
#include <system_error>
#include <Windows.h>
namespace DopeEngine
{
	String WindowsError::get_last_error()
	{
		DWORD errorMessageID = GetLastError();
		return std::system_category().message(errorMessageID).c_str();
	}

}