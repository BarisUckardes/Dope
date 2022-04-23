#include "WindowString.h"
#include <comdef.h>
namespace DopeEngine
{
	String WindowsString::get_string(const wchar_t* wchars)
	{
		/*
		* Convert
		*/
		_bstr_t b(wchars);

		/*
		* Set operator
		*/
		const char* c = b;
		return c;
	}
}