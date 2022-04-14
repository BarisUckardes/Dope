#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>

namespace DopeEngine
{
	/// <summary>
	/// Create description for resource view
	/// </summary>
	struct DOPE_ENGINE_API ResourceViewDescription
	{
		ResourceViewDescription(const Array<DeviceObject*> deviceObjects) : Resources(deviceObjects) {}
		ResourceViewDescription() = default;
		~ResourceViewDescription() = default;

		/// <summary>
		/// The resource array which is bound
		/// </summary>
		Array<DeviceObject*> Resources;
	};
}