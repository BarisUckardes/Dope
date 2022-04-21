#pragma once
#include <Engine/Graphics/Buffer/UniformBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const String& name,const unsigned long allocatedSize,DEVICE device);
		virtual ~OpenGLUniformBuffer() final override;

		 UNIFORM_BUFFER_HANDLE get_handle() const;
		void update(const Byte* data);
	private:
		void create();
		void invalidate();
	private:
		UNIFORM_BUFFER_HANDLE Handle;
		DEVICE Device;
	};


}