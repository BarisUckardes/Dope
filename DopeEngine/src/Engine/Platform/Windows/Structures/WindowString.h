#pragma once
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsString
	{
	public:
		WindowsString() = delete;
		~WindowsString() = delete;

		static String get_string(const wchar_t* wchars);
	};
}