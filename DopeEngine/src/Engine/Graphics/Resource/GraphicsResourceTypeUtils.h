#pragma once
#include <Engine/Graphics/Resource/GraphicsResourceType.h>
#include <Engine/Graphics/Device/GraphicsDeviceObjectType.h>
namespace DopeEngine
{
	/// <summary>
	/// Util operations for resource types
	/// </summary>
	class DOPE_ENGINE_API GraphicsResourceTypeUtils
	{
	public:
		GraphicsResourceTypeUtils() = delete;
		~GraphicsResourceTypeUtils() = delete;

		static GraphicsDeviceObjectType get_device_object_type(const GraphicsResourceType type);
		static GraphicsResourceType get_resource_type(const GraphicsDeviceObjectType type);
	};


}