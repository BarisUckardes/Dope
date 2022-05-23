#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>

namespace DopeEngine
{
	/// <summary>
	/// Create description for resource view
	/// </summary>
	struct DOPE_ENGINE_API GraphicsResourceDesc
	{
		GraphicsResourceDesc(GraphicsDeviceObject* deviceObjects) : Resource(deviceObjects) {}
		GraphicsResourceDesc() = default;
		~GraphicsResourceDesc() = default;

		GraphicsDeviceObject* Resource;
	};
}