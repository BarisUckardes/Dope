#pragma once
#include <Engine/Audio/Loader/AudioLoaderType.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	struct AudioLoadResult;

	/// <summary>
	/// Interface for audio loaders
	/// </summary>
	class DOPE_ENGINE_API IAudioLoader
	{
	public:
		static IAudioLoader* create(const AudioLoaderType requestedLoader);

		IAudioLoader() = default;
		~IAudioLoader() = default;

		virtual AudioLoaderType get_loader_type() const = 0;

		virtual void load(const String& path, AudioLoadResult& result) = 0;
	};
}