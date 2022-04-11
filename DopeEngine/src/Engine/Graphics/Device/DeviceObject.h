#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// A device object which consists of only a debug name
	/// </summary>
	class DOPE_ENGINE_API DeviceObject
	{
	public:
		DeviceObject() : DebugName("Device Object") {}
		~DeviceObject() = default;

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
	private:
		String DebugName;
	};


}