#pragma once
#include <Engine/Audio/State/AudioSourceState.h>
#include <Engine/Audio/API/XAudio2/Core/X2Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API X2SourceState : public AudioSourceState
	{
	public:
		X2SourceState(const AudioSourceStateDesc& desc, const X2AudioDevice* device);
		virtual ~X2SourceState() final override;

		FORCEINLINE IXAudio2SourceVoice* get_x2_source_voice() const;
	private:
		void create(const X2AudioDevice* device);
	private:
		IXAudio2SourceVoice* Source;
	};


}