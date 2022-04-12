#pragma once
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const unsigned long allocatedSize,const unsigned int perVertexSize ,DEVICE device);
		virtual ~OpenGLVertexBuffer() final override;

	protected:
		virtual void update_impl(const Byte* data) override;
	private:
		void create();
		void invalidate();
	private:
		VERTEX_BUFFER_HANDLE Handle;
		DEVICE Device;
	};


}