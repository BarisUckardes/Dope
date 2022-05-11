#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Audio/Device/AudioDeviceObjectType.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		FORCEINLINE String get_name() const;
		FORCEINLINE AudioDeviceObjectType get_type() const;
		FORCEINLINE void set_name(const String& name);

	protected:
		AudioDeviceObject(const AudioDeviceObjectType type) : Type(type) {}
		virtual ~AudioDeviceObject() = default;
	private:
		String Name;
		AudioDeviceObjectType Type;

	};


}