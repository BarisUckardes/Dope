#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>

namespace DopeEngine
{
	/// <summary>
	/// Create description for resource view
	/// </summary>
	struct DOPE_ENGINE_API ResourceViewDescription
	{
		ResourceViewDescription(DeviceObject* deviceObjects) : Resource(deviceObjects) {}
		ResourceViewDescription() = default;
		~ResourceViewDescription() = default;

		/// <summary>
		/// The resource array which is bound
		/// </summary>
		DeviceObject* Resource;
	};
}