#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>

namespace DopeEngine
{
	/// <summary>
	/// Create description for resource view
	/// </summary>
	struct DOPE_ENGINE_API ResourceViewDescription
	{
		ResourceViewDescription(GraphicsDeviceObject* deviceObjects) : Resource(deviceObjects) {}
		ResourceViewDescription() = default;
		~ResourceViewDescription() = default;

		/// <summary>
		/// The resource array which is bound
		/// </summary>
		GraphicsDeviceObject* Resource;
	};
}