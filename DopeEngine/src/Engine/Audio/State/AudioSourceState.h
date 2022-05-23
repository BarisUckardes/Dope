#pragma once
#include <Engine/Audio/Device/AudioDeviceObject.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/Audio/State/AudioSourceStateDesc.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents an audio source state
	/// </summary>
	class DOPE_ENGINE_API AudioSourceState : public AudioDeviceObject
	{
		friend class AudioDevice;
	public:
		FORCEINLINE AudioBufferFormat get_expected_format() const;
		FORCEINLINE Vector3f get_position() const;
		FORCEINLINE Vector3f get_velocity() const;
		FORCEINLINE float get_pitch() const;
		FORCEINLINE float get_gain() const;
		FORCEINLINE bool is_looping() const;
	protected:
		AudioSourceState(const AudioSourceStateDesc& desc);
		virtual ~AudioSourceState() override = default;

	private:
		AudioBufferFormat ExpectedFormat;
		Vector3f Position;
		Vector3f Velocity;
		float Pitch;
		float Gain;
		bool Looping;
	};


}