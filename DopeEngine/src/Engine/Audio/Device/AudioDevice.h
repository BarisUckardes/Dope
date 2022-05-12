#pragma once
#include <Engine/Audio/Device/AudioAPIType.h>
#include <Engine/Structures/Array.h>
#include <Engine/Audio/Buffer/AudioBufferDesc.h>
#include <Engine/Audio/State/AudioListenerStateDesc.h>
#include <Engine/Audio/State/AudioSourceStateDesc.h>
namespace DopeEngine
{
	class AudioBuffer;
	class AudioSourceState;
	class AudioListenerState;
	class AudioDeviceObject;
	class DOPE_ENGINE_API AudioDevice
	{
	public:
		static AudioDevice* create(const AudioAPIType apiType);

		FORCEINLINE AudioAPIType get_api_type() const;
		AudioBuffer* create_buffer(const AudioBufferDesc& desc);
		AudioSourceState* create_source_state(const AudioSourceStateDesc& desc);
		AudioListenerState* create_listener_state(const AudioListenerStateDesc& desc);

		void update_buffer(const Byte* data,AudioBuffer* buffer);
		void update_source_state(const AudioSourceStateDesc& desc,AudioSourceState* state);
		void update_listener_state(const AudioListenerStateDesc& desc, AudioListenerState* state);
		void sumbit_listener(const AudioListenerState* state);
		void submit_source(const AudioSourceState* state, const AudioBuffer* buffer);
		void submit_play_source(const AudioSourceState* state);
	protected:
		AudioDevice(const AudioAPIType apiType);
		virtual ~AudioDevice();

		virtual AudioBuffer* create_buffer_impl(const AudioBufferDesc& desc) = 0;
		virtual AudioSourceState* create_source_state_impl(const AudioSourceStateDesc& desc) = 0;
		virtual AudioListenerState* create_listener_state_impl(const AudioListenerStateDesc& desc) = 0;
		virtual void update_buffer_impl(const Byte* data, AudioBuffer* buffer) = 0;
		virtual void update_source_state_impl(const AudioSourceStateDesc& desc, AudioSourceState* state) = 0;
		virtual void update_listener_state_impl(const AudioListenerStateDesc& desc, AudioListenerState* state) = 0;
		virtual void submit_listener_impl(const AudioListenerState* state) = 0;
		virtual void submit_source_impl(const AudioSourceState* state, const AudioBuffer* buffer) = 0;
		virtual void submit_play_source_impl(const AudioSourceState* state) = 0;
	private:
		void register_device_object(AudioDeviceObject* childObject);
		void delete_device_object(AudioDeviceObject* childObject);
	private:
		Array<AudioDeviceObject*> ChildObjects;
		AudioAPIType Type;
	};
}