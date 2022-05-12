#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API AudioBufferUtils
	{
	public:
		AudioBufferUtils() = delete;
		~AudioBufferUtils() = delete;

		FORCEINLINE static unsigned int get_channel_count(const AudioBufferFormat format);
		FORCEINLINE static unsigned int get_sample_count(const AudioBufferFormat format);
	};


}