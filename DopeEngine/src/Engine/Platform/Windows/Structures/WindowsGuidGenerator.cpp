#include "WindowsGuidGenerator.h"
#include <rpc.h>
#include <stdio.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	void WindowsGuidGenerator::create_guid(Guid& guid)
	{
		const HRESULT createHR = CoCreateGuid((GUID*)&guid);
		ASSERT(SUCCEEDED(createHR), "WindowsGuidGenerator", "Guid creation failed!");
	}

}