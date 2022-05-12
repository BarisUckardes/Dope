#pragma once
#include <Engine/Audio/Buffer/AudioBuffer.h>
#include <Engine/Audio/API/XAudio2/Core/X2Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API X2Buffer : public AudioBuffer
	{
	public:
		X2Buffer(const AudioBufferDesc& desc,const X2AudioDevice* device);
		virtual ~X2Buffer() final override;

		FORCEINLINE XAUDIO2_BUFFER get_x2_buffer() const;
	private:
		void create(const X2AudioDevice* device);
	private:
		XAUDIO2_BUFFER Buffer;
	};


}