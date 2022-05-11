#include "OpenALBuffer.h"

namespace DopeEngine
{
	OpenALBuffer::OpenALBuffer(const AudioBufferDesc& desc) : AudioBuffer(desc)
	{
		/*
		* Create buffer handle
		*/
		alGenBuffers(1, &Handle);
	}

	OpenALBuffer::~OpenALBuffer()
	{
		alDeleteBuffers(1, &Handle);
	}

	BUFFER_HANDLE OpenALBuffer::get_al_buffer_handle() const
	{
		return Handle;
	}

}