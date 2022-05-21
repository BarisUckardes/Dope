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

		/// <summary>
		/// Return device object type
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		static GraphicsDeviceObjectType get_device_object_type(const GraphicsResourceType type);

		/// <summary>
		/// Returns the resource type out of GraphicsDeviceObject
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		static GraphicsResourceType get_resource_type(const GraphicsDeviceObjectType type);
	};


}