#pragma once
#include <Engine/Math/Vector3f.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API AudioListenerStateDesc
	{
		AudioListenerStateDesc() : Orientation(0) {}
		~AudioListenerStateDesc() = default;


		Vector3f Position;
		Vector3f Velocity;
		float Orientation;
	};
}