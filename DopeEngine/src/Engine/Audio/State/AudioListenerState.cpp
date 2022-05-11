#include "AudioListenerState.h"


namespace DopeEngine
{
	Vector3f AudioListenerState::get_position() const
	{
		return Position;
	}

	Vector3f AudioListenerState::get_velocity() const
	{
		return Velocity;
	}

	float AudioListenerState::get_orientation() const
	{
		return Orientation;
	}

	AudioListenerState::AudioListenerState(const AudioListenerStateDesc& desc) : AudioDeviceObject(AudioDeviceObjectType::ListenerState)
	{
		Position = desc.Position;
		Velocity = desc.Velocity;
		Orientation = desc.Orientation;
	}



}