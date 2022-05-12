#include "X2Buffer.h"

namespace DopeEngine
{
	X2Buffer::X2Buffer(const AudioBufferDesc& desc, const X2AudioDevice* device) : AudioBuffer(desc)
	{
		create(device);
	}

	X2Buffer::~X2Buffer()
	{

	}

	XAUDIO2_BUFFER X2Buffer::get_x2_buffer() const
	{
		return Buffer;
	}

	void X2Buffer::create(const X2AudioDevice* device)
	{

	}

}