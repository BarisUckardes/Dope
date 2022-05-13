#pragma once
#include <Engine/Audio/Loader/IAudioLoader.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WavAudioLoader : public IAudioLoader
	{
	public:
		WavAudioLoader() = default;
		~WavAudioLoader() = default;


		// Inherited via IAudioLoader
		virtual AudioLoaderType get_loader_type() const override;
		virtual void load(const String& path, AudioLoadResult& result) override;
	};


}