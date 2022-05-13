#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API WavFileData
	{
		char ChunkID[4];
		unsigned int ChunkSize;
		char Format[4];
		char SubChunkID[4];
		unsigned int SubChunkSize;
		unsigned short AudioFormat;
		unsigned short Channels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAlign;
		unsigned short BitsPerSample;
		char SubChunkID1[4];
		unsigned int SubChunk1Size;
	};
}