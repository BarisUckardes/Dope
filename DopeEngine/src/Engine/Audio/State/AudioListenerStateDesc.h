#pragma once
#include <Engine/Math/Vector3f.h>

namespace DopeEngine
{

	/// <summary>
	/// Required fields to create an AudioListenerState
	/// </summary>
	struct DOPE_ENGINE_API AudioListenerStateDesc
	{
		AudioListenerStateDesc() : Orientation(0) {}
		~AudioListenerStateDesc() = default;

		/// <summary>
		/// Position of the listener
		/// </summary>
		Vector3f Position;

		/// <summary>
		/// Velocity of the listener
		/// </summary>
		Vector3f Velocity;

		/// <summary>
		/// Orientation of the listener
		/// </summary>
		float Orientation;
	};
}