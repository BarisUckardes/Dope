#include "WindowsGuidGenerator.h"
#include <rpc.h>
#include <stdio.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	void WindowsGuidGenerator::create_guid(Guid& guid)
	{
		/*
		* Create
		*/
		const HRESULT createHR = CoCreateGuid((GUID*)&guid);

		/*
		* Validate creation
		*/
		ASSERT(SUCCEEDED(createHR), "WindowsGuidGenerator", "Guid creation failed!");
	}

}