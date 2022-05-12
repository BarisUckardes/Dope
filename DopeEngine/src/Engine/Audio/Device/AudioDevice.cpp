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
			case DopeEngine::AudioAPIType::DirectSound:
				break;
			default:
				break;
		}
    }

	AudioAPIType AudioDevice::get_api_type() const
	{
		return Type;
	}

	AudioBuffer* AudioDevice::create_buffer(const AudioBufferDesc& desc)
	{
		/*
		* Create buffer
		*/
		AudioBuffer* buffer = create_buffer_impl(desc);

		/*
		* Register buffer
		*/
		register_device_object(buffer);

		return buffer;
	}

	AudioSourceState* AudioDevice::create_source_state(const AudioSourceStateDesc& desc)
	{
		/*
		* Create state
		*/
		AudioSourceState* state = create_source_state_impl(desc);

		/*
		* Register state
		*/
		register_device_object(state);

		return state;
	}

	AudioListenerState* AudioDevice::create_listener_state(const AudioListenerStateDesc& desc)
	{
		/*
		* Create state
		*/
		AudioListenerState* state = create_listener_state_impl(desc);

		/*
		* Register state
		*/
		register_device_object(state);

		return state;
	}

	void AudioDevice::update_buffer(const Byte* data, AudioBuffer* buffer)
	{
		/*
		* Call api impl
		*/
		update_buffer_impl(data, buffer);
	}

	void AudioDevice::update_source_state(const AudioSourceStateDesc& desc, AudioSourceState* state)
	{
		/*
		* Call api impl
		*/
		update_source_state_impl(desc, state);

		/*
		* Update state
		*/
		state->Position = desc.Position;
		state->Velocity = desc.Velocity;
		state->Gain = desc.Gain;
		state->Pitch = desc.Pitch;
		state->Looping = desc.Looping;
	}

	void AudioDevice::update_listener_state(const AudioListenerStateDesc& desc, AudioListenerState* state)
	{
		/*
		* Call api impl
		*/
		update_listener_state_impl(desc, state);

		/*
		* Update state
		*/
		state->Position = desc.Position;
		state->Velocity = desc.Velocity;
		state->Orientation = desc.Orientation;
	}

	void AudioDevice::sumbit_listener(const AudioListenerState* state)
	{
		/*
		* Call api impl
		*/
		submit_listener_impl(state);
	}

	void AudioDevice::submit_source(const AudioSourceState* state, const AudioBuffer* buffer)
	{
		/*
		* Validate match
		*/
		ASSERT(state->get_expected_format() == buffer->get_format(), "AudioDevice", "AudioSourceState and AudioBuffer formats dont match!");

		/*
		* Call api impl
		*/
		submit_source_impl(state, buffer);
	}

	void AudioDevice::submit_play_source(const AudioSourceState* state)
	{
		/*
		* call api impl
		*/
		submit_play_source_impl(state);
	}

	AudioDevice::AudioDevice(const AudioAPIType apiType) : Type(apiType)
	{

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
		/*
		* Validate if this is a child object
		*/
		const int index = ChildObjects.find_index(childObject);
		if (index == -1)
			return;

		/*
		* Delete
		*/
		ChildObjects.remove(childObject);
		delete childObject;
	}

}