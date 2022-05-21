#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	/// <summary>
	/// Util operations for AudioBuffers
	/// </summary>
	class DOPE_ENGINE_API AudioBufferUtils
	{
	public:
		AudioBufferUtils() = delete;
		~AudioBufferUtils() = delete;

		/// <summary>
		/// Returns the raw channel count
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		FORCEINLINE static unsigned int get_channel_count(const AudioBufferFormat format);

		/// <summary>
		/// Returns the raw sample count
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		FORCEINLINE static unsigned int get_sample_count(const AudioBufferFormat format);
	};


}