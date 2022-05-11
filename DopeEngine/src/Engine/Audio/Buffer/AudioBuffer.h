#pragma once
#include <Engine/Audio/Device/AudioDeviceObject.h>
#include <Engine/Audio/Buffer/AudioBufferDesc.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API AudioBuffer : public AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		FORCEINLINE unsigned long get_allocated_size() const;
		FORCEINLINE unsigned long get_frequency() const;
		FORCEINLINE AudioBufferFormat get_format() const;
	protected:
		AudioBuffer(const AudioBufferDesc& desc);
		~AudioBuffer() = default;
	private:
		unsigned long AllocatedSize;
		unsigned long Frequency;
		AudioBufferFormat Format;
	};


}