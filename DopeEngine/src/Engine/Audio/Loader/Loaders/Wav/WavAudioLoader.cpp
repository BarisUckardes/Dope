#include "WavAudioLoader.h"


namespace DopeEngine
{
	AudioLoaderType WavAudioLoader::get_loader_type() const
	{
		return AudioLoaderType::Wav;
	}

	void WavAudioLoader::load(const String& path, AudioLoadResult& result)
	{

	}

}