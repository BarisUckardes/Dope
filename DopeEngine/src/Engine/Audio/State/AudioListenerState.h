#pragma once
#include <Engine/Audio/Device/AudioDeviceObject.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/Audio/State/AudioListenerStateDesc.h>

namespace DopeEngine
{
	/// <summary>
	/// Represents a listener state in spatial space
	/// </summary>
	class DOPE_ENGINE_API AudioListenerState : public AudioDeviceObject
	{
		friend class AudioDevice;
	public:

		/// <summary>
		/// Returns the position of the listener
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_position() const;

		/// <summary>
		/// Returns the velocity of the listener
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_velocity() const;

		/// <summary>
		/// Returns the orientation of the listener
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float get_orientation() const;
	protected:
		AudioListenerState(const AudioListenerStateDesc& desc);
		virtual ~AudioListenerState() override = default;
	private:
		Vector3f Position;
		Vector3f Velocity;
		float Orientation;
	};


}