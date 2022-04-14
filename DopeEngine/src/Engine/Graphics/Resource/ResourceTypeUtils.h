#pragma once
#include <Engine/Graphics/Resource/ResourceType.h>
#include <Engine/Graphics/Device/DeviceObjectType.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API ResourceTypeUtils
	{
	public:
		ResourceTypeUtils() = delete;
		~ResourceTypeUtils() = delete;

		/// <summary>
		/// Return device object type
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		static FORCEINLINE DeviceObjectType get_device_object_type(const ResourceType type);
	};


}