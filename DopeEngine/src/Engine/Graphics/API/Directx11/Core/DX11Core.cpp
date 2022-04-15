#include "DX11Core.h"
#include <comdef.h>
#include <Engine/Core/Assert.h>
#include <string>
void _handle_error(HRESULT h)
{
	_com_error err(h);
	LPCTSTR errMsg = err.ErrorMessage();
	std::wstring wstr(errMsg);
	ASSERT(SUCCEEDED(h), "DX11ErrorHandle", "Error Message: %s",wstr.c_str());
}