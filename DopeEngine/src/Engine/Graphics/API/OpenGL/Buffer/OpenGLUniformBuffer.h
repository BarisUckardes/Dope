#pragma once
#include <Engine/Graphics/Buffer/UniformBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const unsigned long allocatedSize,DEVICE device);
		virtual ~OpenGLUniformBuffer() final override;

	protected:
		virtual void update_impl(const Byte* data) override;
	private:
		void create();
		void invalidate();
	private:
		INDEX_BUFFER_HANDLE Handle;
		DEVICE Device;
	};


}