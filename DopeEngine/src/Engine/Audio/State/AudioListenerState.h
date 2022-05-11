#pragma once
#include <Engine/Audio/Device/AudioDeviceObject.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/Audio/State/AudioListenerStateDesc.h>

namespace DopeEngine
{
	class AudioListenerState : public AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		FORCEINLINE Vector3f get_position() const;
		FORCEINLINE Vector3f get_velocity() const;
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