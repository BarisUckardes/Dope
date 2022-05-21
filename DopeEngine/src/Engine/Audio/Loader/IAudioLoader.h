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
		/// <summary>
		/// Creates the requested loader
		/// </summary>
		/// <param name="requestedLoader"></param>
		/// <returns></returns>
		static IAudioLoader* create(const AudioLoaderType requestedLoader);
		IAudioLoader() = default;
		~IAudioLoader() = default;

		/// <summary>
		/// Returns the loader type
		/// </summary>
		/// <returns></returns>
		virtual AudioLoaderType get_loader_type() const = 0;

		/// <summary>
		/// Loads the audio file on the given path
		/// </summary>
		/// <param name="path"></param>
		/// <param name="result"></param>
		virtual void load(const String& path, AudioLoadResult& result) = 0;
	};
}