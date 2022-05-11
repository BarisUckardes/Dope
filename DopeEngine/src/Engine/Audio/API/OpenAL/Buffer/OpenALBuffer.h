#pragma once
#include <Engine/Audio/Buffer/AudioBuffer.h>
#include <Engine/Audio/API/OpenAL/Core/OpenALCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenALBuffer : public AudioBuffer
	{
	public:
		OpenALBuffer(const AudioBufferDesc& desc);
		virtual ~OpenALBuffer() final override;

		FORCEINLINE BUFFER_HANDLE get_al_buffer_handle() const;
	private:
		BUFFER_HANDLE Handle;
	};


}