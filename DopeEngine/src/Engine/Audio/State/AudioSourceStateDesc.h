#pragma once
#include <Engine/Math/Vector3f.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	/// <summary>
	/// Required fields to create an AudioSourceState
	/// </summary>
	struct DOPE_ENGINE_API AudioSourceStateDesc
	{
		AudioSourceStateDesc() :Pitch(0),Gain(0),Looping(false),ExpectedFormat() {}
		~AudioSourceStateDesc() = default;

		/// <summary>
		/// Expected buffer format
		/// </summary>
		AudioBufferFormat ExpectedFormat;

		/// <summary>
		/// Initial position
		/// </summary>
		Vector3f Position;

		/// <summary>
		/// Initial velocity
		/// </summary>
		Vector3f Velocity;

		/// <summary>
		/// Initial pitch value
		/// </summary>
		float Pitch;

		/// <summary>
		/// Initial gain value
		/// </summary>
		float Gain;

		/// <summary>
		/// Whether its looping or not
		/// </summary>
		bool Looping;
	};
}