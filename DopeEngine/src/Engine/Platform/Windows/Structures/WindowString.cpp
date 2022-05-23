#include "WindowString.h"
#include <comdef.h>
namespace DopeEngine
{
	String WindowsString::get_string(const wchar_t* wchars)
	{
		_bstr_t b(wchars);

		const char* c = b;

		return c;
	}
}