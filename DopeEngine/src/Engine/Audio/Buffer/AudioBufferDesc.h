#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	/// <summary>
	/// Required fields to create and audiobuffer
	/// </summary>
	struct DOPE_ENGINE_API AudioBufferDesc
	{
		AudioBufferDesc() : AllocatedSize(0),Frequency(0), Format(AudioBufferFormat::Undefined) {}
		~AudioBufferDesc() = default;

		/// <summary>
		/// Total buffer size in bytes
		/// </summary>
		unsigned long AllocatedSize;

		/// <summary>
		/// Buffer frequency
		/// </summary>
		unsigned long Frequency;

		/// <summary>
		/// Buffer format
		/// </summary>
		AudioBufferFormat Format;
	};
}