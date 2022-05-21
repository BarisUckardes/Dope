#pragma once
#include <Engine/Audio/Device/AudioDevice.h>
#include <Engine/Audio/API/OpenAL/Core/OpenALCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenALAudioDevice : public AudioDevice
	{
	public:
		OpenALAudioDevice();
		virtual ~OpenALAudioDevice() final override;
	protected:
		virtual AudioAPIType get_api_type() const override;
		virtual AudioBuffer* create_buffer_impl(const AudioBufferDesc& desc) override;
		virtual AudioSourceState* create_source_state_impl(const AudioSourceStateDesc& desc) override;
		virtual AudioListenerState* create_listener_state_impl(const AudioListenerStateDesc& desc) override;
		virtual void update_buffer_impl(const Byte* data, AudioBuffer* buffer) override;
		virtual void update_source_state_impl(const AudioSourceStateDesc& desc, AudioSourceState* state) override;
		virtual void update_listener_state_impl(const AudioListenerStateDesc& desc, AudioListenerState* state) override;
		virtual void submit_listener_impl(const AudioListenerState* state) override;
		virtual void submit_source_impl(const AudioSourceState* state, const AudioBuffer* buffer) override;
		virtual void submit_play_source_impl(const AudioSourceState* state) override;
	private:
		void create();
	private:
		ALCdevice* Device;
		ALCcontext* Context;

		
	};
}