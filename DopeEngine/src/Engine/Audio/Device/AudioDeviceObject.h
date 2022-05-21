#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Audio/Device/AudioDeviceObjectType.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents a object which's created and authored by an AudioDevice
	/// </summary>
	class DOPE_ENGINE_API AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		/// <summary>
		/// Returns the device object name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_name() const;

		/// <summary>
		/// Returns the device object type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AudioDeviceObjectType get_type() const;

		/// <summary>
		/// Sets the name of the device object
		/// </summary>
		/// <param name="name"></param>
		FORCEINLINE void set_name(const String& name);

	protected:
		AudioDeviceObject(const AudioDeviceObjectType type) : Type(type) {}
		virtual ~AudioDeviceObject() = default;
	private:
		String Name;
		AudioDeviceObjectType Type;

	};


}