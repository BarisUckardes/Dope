#pragma once
#include <Engine/Math/Vector3f.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API AudioSourceStateDesc
	{
		AudioSourceStateDesc() :Pitch(0),Gain(0),Looping(false) {}
		~AudioSourceStateDesc() = default;

		Vector3f Position;
		Vector3f Velocity;
		float Pitch;
		float Gain;
		bool Looping;
	};
}