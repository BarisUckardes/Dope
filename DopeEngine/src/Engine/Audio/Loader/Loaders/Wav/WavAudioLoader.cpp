#include "WavAudioLoader.h"
#include <Engine/File/PlatformFile.h>
#include <Engine/Memory/ByteBlock.h>
#include <Engine/Audio/Loader/AudioLoadResult.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEngine
{
	AudioLoaderType WavAudioLoader::get_loader_type() const
	{
		return AudioLoaderType::Wav;
	}

	void WavAudioLoader::load(const String& path, AudioLoadResult& result)
	{
		/*
		* Load .wav header
		*/
		ByteBlock headerBlock;
		const bool isFileValid = PlatformFile::read(path,headerBlock,0,44);

		/*
		* Validate file
		*/
		if (!isFileValid)
		{
			LOG("WavAudioLoader", "Couldnt read the file on the specified path");
			return;
		}

		/*
		* Header block to wav data
		*/
		WavFileHeaderData headerData = headerBlock.to<WavFileHeaderData>();

		/*
		* Validate if .wav file
		*/

		/*
		* Load wav file content
		*/
		ByteBlock audioContent;
		const bool readingAudioContentOK = PlatformFile::read(path, audioContent, 44, headerData.ChunkSize);

		/*
		* Create result
		*/
	}

}