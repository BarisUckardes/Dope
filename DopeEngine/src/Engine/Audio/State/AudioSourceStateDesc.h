#pragma once
#include <Engine/Math/Vector3f.h>
#include <Engine/Audio/Buffer/AudioBufferFormat.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API AudioSourceStateDesc
	{
		AudioSourceStateDesc() :Pitch(0),Gain(0),Looping(false),ExpectedFormat() {}
		~AudioSourceStateDesc() = default;

		AudioBufferFormat ExpectedFormat;
		Vector3f Position;
		Vector3f Velocity;
		float Pitch;
		float Gain;
		bool Looping;
	};
}