#include "X2SourceState.h"
#include <Engine/Audio/API/XAudio2/Device/X2AudioDevice.h>
#include <Engine/Audio/Buffer/AudioBufferUtils.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	X2SourceState::X2SourceState(const AudioSourceStateDesc& desc, const X2AudioDevice* device) : AudioSourceState(desc)
	{
		create(device);
	}

	X2SourceState::~X2SourceState()
	{

	}

	IXAudio2SourceVoice* X2SourceState::get_x2_source_voice() const
	{
		return Source;
	}

	void X2SourceState::create(const X2AudioDevice* device)
	{
		/*
		* Get engine
		*/
		X2PTR<X2Engine> x2Engine = device->get_x2_engine();

		/*
		* Create source WAVEFORMATEX
		*/
		const AudioBufferFormat expectedFormat = get_expected_format();
		WAVEFORMATEX format = {};
		format.nChannels = AudioBufferUtils::get_channel_count(expectedFormat);
		format.nSamplesPerSec = AudioBufferUtils::get_sample_count(expectedFormat);

		/*
		* Create source voice
		*/
		const HRESULT createSourceHR = x2Engine->CreateSourceVoice(&Source,&format);

		/*
		* Validate source voice creation
		*/
		ASSERT(SUCCEEDED(createSourceHR), "X2SourceState", "Source voice creation failed!");
	}

}