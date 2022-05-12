#include "X2AudioDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Audio/API/XAudio2/Device/X2AudioDeviceObjects.h>
namespace DopeEngine
{
	X2AudioDevice::X2AudioDevice() : AudioDevice(AudioAPIType::DirectSound)
	{
		/*
		* Create engine instance
		*/
		const HRESULT engineCreateHR = XAudio2Create(EngineInstance.GetAddressOf(), 0, XAUDIO2_DEFAULT_PROCESSOR);

		/*
		* Validate engine creation
		*/
		ASSERT(SUCCEEDED(engineCreateHR), "X2AudioDevice", "Failed to create engine!");

		/*
		* Create device
		*/
		const HRESULT deviceCreateHR = EngineInstance->CreateMasteringVoice(&Device);

		/*
		* Validate device creation
		*/
		ASSERT(SUCCEEDED(deviceCreateHR),"X2AudioDevice","Failed to create device!");
	}
	X2AudioDevice::~X2AudioDevice()
	{

	}
	X2PTR<X2Engine> X2AudioDevice::get_x2_engine() const
	{
		return EngineInstance;
	}
	X2Device* X2AudioDevice::get_x2_device() const
	{
		return Device;
	}
	AudioBuffer* X2AudioDevice::create_buffer_impl(const AudioBufferDesc& desc)
	{
		return nullptr;
	}

	AudioSourceState* X2AudioDevice::create_source_state_impl(const AudioSourceStateDesc& desc)
	{
		return nullptr;
	}

	AudioListenerState* X2AudioDevice::create_listener_state_impl(const AudioListenerStateDesc& desc)
	{
		return nullptr;
	}

	void X2AudioDevice::update_buffer_impl(const Byte* data, AudioBuffer* buffer)
	{

	}

	void X2AudioDevice::update_source_state_impl(const AudioSourceStateDesc& desc, AudioSourceState* state)
	{

	}

	void X2AudioDevice::update_listener_state_impl(const AudioListenerStateDesc& desc, AudioListenerState* state)
	{

	}

	void X2AudioDevice::submit_listener_impl(const AudioListenerState* state)
	{

	}

	void X2AudioDevice::submit_source_impl(const AudioSourceState* state, const AudioBuffer* buffer)
	{
		/*
		* Get x2 source state
		*/
		const X2SourceState* x2State = (const X2SourceState*)state;

		/*
		* Get x2 audio buffer
		*/
		const X2Buffer* x2Buffer = (const X2Buffer*)buffer;

		/*
		* Bind buffer to source state
		*/
		const XAUDIO2_BUFFER audioBuffer = x2Buffer->get_x2_buffer();

		/*
		* Submit buffer to source
		*/
		const HRESULT submitHR = x2State->get_x2_source_voice()->SubmitSourceBuffer(&audioBuffer);

		/*
		* Validate submit
		*/
		ASSERT(SUCCEEDED(submitHR), "X2AudioDevice", "Couldnt submit buffer to source voice");
	}

	void X2AudioDevice::submit_play_source_impl(const AudioSourceState* state)
	{
		/*
		* Get x2 source state
		*/
		const X2SourceState* x2State = (const X2SourceState*)state;

		/*
		* Play source
		*/
		HRESULT startHR = x2State->get_x2_source_voice()->Start();

		/*
		* Validate start
		*/
		ASSERT(SUCCEEDED(startHR), "X2AudioDevice", "Couldnt start the source voice!");
	}

}