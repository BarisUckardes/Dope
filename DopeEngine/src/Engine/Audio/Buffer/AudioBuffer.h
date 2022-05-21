#pragma once
#include <Engine/Audio/Device/AudioDeviceObject.h>
#include <Engine/Audio/Buffer/AudioBufferDesc.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents a audio data buffer
	/// </summary>
	class DOPE_ENGINE_API AudioBuffer : public AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		/// <summary>
		/// Returns the total allocated size in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_allocated_size() const;

		/// <summary>
		/// Returns the frequency of the audio buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_frequency() const;

		/// <summary>
		/// Returns the format of the buffer
		/// </summary>
		/// <returns></returns>
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