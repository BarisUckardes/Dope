#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API TextureLoadResult
	{
		TextureLoadResult(const Byte* data,const String& failureMessage,unsigned int channels,unsigned int width,unsigned int height,unsigned int depth) :
			Data(data),FailureMessage(failureMessage),ChannelCount(channels),Width(width),Height(height),Depth(depth)
		{}
		TextureLoadResult() = default;
		~TextureLoadResult() = default;

		/// <summary>
		/// The data returned
		/// </summary>
		const Byte* Data;

		/// <summary>
		/// The failure message 
		/// </summary>
		String FailureMessage;

		/// <summary>
		/// Channel count R-G-B,R-G-B-A
		/// </summary>
		unsigned int ChannelCount;

		/// <summary>
		/// Width of the texture in pixels
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Height of the texture in pixels
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Depth of the texture in pixels
		/// </summary>
		unsigned int Depth;
	};
}