#include "AudioDevice.h"
#include <Engine/Audio/API/OpenAL/Device/OpenALAudioDevice.h>
#include <Engine/Audio/API/XAudio2/Device/X2AudioDevice.h>
#include <Engine/Audio/Device/AudioDeviceObjects.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
    AudioDevice* AudioDevice::create(AudioAPIType apiType)
    {
		switch (apiType)
		{
			case DopeEngine::AudioAPIType::Undefined:
				return new X2AudioDevice();
				break;
			case DopeEngine::AudioAPIType::OpenAL:
				return new OpenALAudioDevice();
				break;
			case DopeEngine::AudioAPIType::X2Audio:
				break;
			default:
				break;
		}
    }


	AudioBuffer* AudioDevice::create_buffer(const AudioBufferDesc& desc)
	{
		AudioBuffer* buffer = create_buffer_impl(desc);
		register_device_object(buffer);

		return buffer;
	}

	AudioSourceState* AudioDevice::create_source_state(const AudioSourceStateDesc& desc)
	{
		AudioSourceState* state = create_source_state_impl(desc);
		register_device_object(state);

		return state;
	}

	AudioListenerState* AudioDevice::create_listener_state(const AudioListenerStateDesc& desc)
	{
		AudioListenerState* state = create_listener_state_impl(desc);
		register_device_object(state);

		return state;
	}

	void AudioDevice::update_buffer(const Byte* data, AudioBuffer* buffer)
	{
		update_buffer_impl(data, buffer);
	}

	void AudioDevice::update_source_state(const AudioSourceStateDesc& desc, AudioSourceState* state)
	{
		update_source_state_impl(desc, state);
		state->Position = desc.Position;
		state->Velocity = desc.Velocity;
		state->Gain = desc.Gain;
		state->Pitch = desc.Pitch;
		state->Looping = desc.Looping;
	}

	void AudioDevice::update_listener_state(const AudioListenerStateDesc& desc, AudioListenerState* state)
	{
		update_listener_state_impl(desc, state);
		state->Position = desc.Position;
		state->Velocity = desc.Velocity;
		state->Orientation = desc.Orientation;
	}

	void AudioDevice::sumbit_listener(const AudioListenerState* state)
	{
		submit_listener_impl(state);
	}

	void AudioDevice::submit_source(const AudioSourceState* state, const AudioBuffer* buffer)
	{
		ASSERT(state->get_expected_format() == buffer->get_format(), "AudioDevice", "AudioSourceState and AudioBuffer formats dont match!");

		submit_source_impl(state, buffer);
	}

	void AudioDevice::submit_play_source(const AudioSourceState* state)
	{
		submit_play_source_impl(state);
	}

	AudioDevice::~AudioDevice()
	{
		for (unsigned int i = 0; i < ChildObjects.get_cursor(); i++)
		{
			delete ChildObjects[i];
		}
		ChildObjects.clear();
	}

	void AudioDevice::register_device_object(AudioDeviceObject* childObject)
	{
		ChildObjects.add(childObject);
	}

	void AudioDevice::delete_device_object(AudioDeviceObject* childObject)
	{
		const int index = ChildObjects.find_index(childObject);
		if (index == -1)
			return;

		ChildObjects.remove(childObject);
		delete childObject;
	}

}