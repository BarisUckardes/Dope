#include "OpenALBufferFormatUtils.h"
#include <Engine/Core/Assert.h>
#include <Engine/Audio/API/OpenAL/Core/OpenALCore.h>
namespace DopeEngine
{
	unsigned int OpenALBufferFormatUtils::get_al_buffer_format(const AudioBufferFormat format)
	{
		switch (format)
		{
			case DopeEngine::AudioBufferFormat::Undefined:
				ASSERT(false, "OpenALBufferFormatUtils", "Undefined AudioBufferFormat, couldnt produce ALenum");
				break;
			case DopeEngine::AudioBufferFormat::Mono8Bit:
				return AL_FORMAT_MONO8;
				break;
			case DopeEngine::AudioBufferFormat::Mono16Bit:
				return AL_FORMAT_MONO16;
				break;
			case DopeEngine::AudioBufferFormat::Stereo8Bit:
				return AL_FORMAT_STEREO8;
				break;
			case DopeEngine::AudioBufferFormat::Stereo16Bit:
				return AL_FORMAT_STEREO16;
				break;
			default:
				ASSERT(false, "OpenALBufferFormatUtils", "Invalid AudioBufferFormat, couldnt produce ALenum");
				break;
		}
	}

}