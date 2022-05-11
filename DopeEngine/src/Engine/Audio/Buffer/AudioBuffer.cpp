#include "AudioBuffer.h"

namespace DopeEngine
{
	unsigned long AudioBuffer::get_allocated_size() const
	{
		return AllocatedSize;
	}

	unsigned long AudioBuffer::get_frequency() const
	{
		return Frequency;
	}

	AudioBufferFormat AudioBuffer::get_format() const
	{
		return Format;
	}

	AudioBuffer::AudioBuffer(const AudioBufferDesc& desc) : AudioDeviceObject(AudioDeviceObjectType::Buffer)
	{
		AllocatedSize = desc.AllocatedSize;
		Format = desc.Format;
		Frequency = desc.Frequency;
	}

}