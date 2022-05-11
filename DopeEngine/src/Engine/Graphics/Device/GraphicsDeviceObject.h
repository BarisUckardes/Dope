#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Device/GraphicsDeviceObjectType.h>
namespace DopeEngine
{
	/// <summary>
	/// A device object which consists of only a debug name
	/// </summary>
	class DOPE_ENGINE_API GraphicsDeviceObject
	{
		friend class GraphicsDevice;
	public:
		/// <summary>
		/// Returns the debug name for this device object
		/// </summary>
		/// <returns></returns>
		String get_debug_name() const;

		/// <summary>
		/// Sets the debug name for this device object
		/// </summary>
		/// <param name="name"></param>
		void set_debug_name(const String& name);

		/// <summary>
		/// Returns the type of this device object
		/// </summary>
		/// <returns></returns>
		GraphicsDeviceObjectType get_device_object_type() const;
	protected:
		GraphicsDeviceObject(const GraphicsDeviceObjectType type) : DebugName("Device Object"),Type(type) {}
		virtual ~GraphicsDeviceObject() = 0 {}
	private:
		String DebugName;
		GraphicsDeviceObjectType Type;
	};


}