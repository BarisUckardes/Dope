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
		/// <summary>
		/// Returns the source buffer format
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AudioBufferFormat get_expected_format() const;

		/// <summary>
		/// Returns the position of the source
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_position() const;

		/// <summary>
		/// Returns the velocity of the source
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_velocity() const;

		/// <summary>
		/// Returns the pitch value
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float get_pitch() const;

		/// <summary>
		/// Returns the gain value
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float get_gain() const;

		/// <summary>
		/// Returns whether its looping or not
		/// </summary>
		/// <returns></returns>
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