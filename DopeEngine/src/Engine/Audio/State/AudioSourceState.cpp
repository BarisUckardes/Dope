#include "AudioSourceState.h"

namespace DopeEngine
{
	AudioSourceState::AudioSourceState(const AudioSourceStateDesc& desc) : AudioDeviceObject(AudioDeviceObjectType::SourceState)
	{
		ExpectedFormat = desc.ExpectedFormat;
		Position = desc.Position;
		Velocity = desc.Velocity;
		Pitch = desc.Pitch;
		Gain = desc.Gain;
		Looping = desc.Looping;
	}


	AudioBufferFormat AudioSourceState::get_expected_format() const
	{
		return ExpectedFormat;
	}

	Vector3f AudioSourceState::get_position() const
	{
		return Position;
	}

	Vector3f AudioSourceState::get_velocity() const
	{
		return Velocity;
	}

	float AudioSourceState::get_pitch() const
	{
		return Pitch;
	}

	float AudioSourceState::get_gain() const
	{
		return Gain;
	}

	bool AudioSourceState::is_looping() const
	{
		return Looping;
	}

}