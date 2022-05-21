#pragma once
#include <Engine/Audio/Loader/IAudioLoader.h>

namespace DopeEngine
{
	/// <summary>
	/// .wav file audio loader implementation
	/// </summary>
	class DOPE_ENGINE_API WavAudioLoader : public IAudioLoader
	{
	public:
		WavAudioLoader() = default;
		~WavAudioLoader() = default;


		// Inherited via IAudioLoader
		virtual AudioLoaderType get_loader_type() const override;
		virtual void load(const String& path, AudioLoadResult& result) override;

	private:
		/// <summary>
		/// Officail .wav file data header
		/// </summary>
		struct WavFileHeaderData
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
	};


}