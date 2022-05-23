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

		unsigned long AllocatedSize;
		unsigned long Frequency;
		AudioBufferFormat Format;
	};
}