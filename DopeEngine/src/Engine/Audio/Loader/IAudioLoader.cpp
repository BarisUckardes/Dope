#include "IAudioLoader.h"
#include <Engine/Audio/Loader/Loaders/Wav/WavAudioLoader.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	IAudioLoader* IAudioLoader::create( AudioLoaderType requestedLoader)
	{
		switch (requestedLoader)
		{
			case DopeEngine::AudioLoaderType::Undefined:
				ASSERT(false, "IAudioLoader", "Undefined AudioLoaderType requested!");
				break;
			case DopeEngine::AudioLoaderType::Wav:
				return new WavAudioLoader();
				break;
			default:
				ASSERT(false, "IAudioLoader", "Invalid AudioLoaderType requested!");
				break;
		}
	}

}