#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	class OpenALBufferFormatUtils
	{
	public:
		OpenALBufferFormatUtils() = delete;
		~OpenALBufferFormatUtils() = delete;

		static unsigned int get_al_buffer_format(const AudioBufferFormat format);
	};


}