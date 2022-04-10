#include "WindowsGuid.h"
#include <rpc.h>
#include <stdio.h>
namespace DopeEngine
{
	void WindowsGuid::create_guid(Guid& guid)
	{
		/*
		* Call windows impl of guid
		*/
		CoCreateGuid((GUID*)&guid);
	}
}