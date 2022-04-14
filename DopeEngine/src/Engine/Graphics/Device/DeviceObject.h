#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Device/DeviceObjectType.h>
namespace DopeEngine
{
	/// <summary>
	/// A device object which consists of only a debug name
	/// </summary>
	class DOPE_ENGINE_API DeviceObject
	{
		friend class GraphicsDevice;
	public:
		/// <summary>
		/// Returns the debug name for this device object
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_debug_name() const;

		/// <summary>
		/// Sets the debug name for this device object
		/// </summary>
		/// <param name="name"></param>
		FORCEINLINE void set_debug_name(const String& name);

		/// <summary>
		/// Returns the type of this device object
		/// </summary>
		/// <returns></returns>
		FORCEINLINE DeviceObjectType get_device_object_type() const;
	protected:
		DeviceObject(const DeviceObjectType type) : DebugName("Device Object"),Type(type) {}
		virtual ~DeviceObject() = 0 {}
	private:
		String DebugName;
		DeviceObjectType Type;
	};


}