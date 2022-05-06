#pragma once
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const BufferDescription& desc,DEVICE device);
		virtual ~OpenGLVertexBuffer() final override;

		/// <summary>
		/// Returns the opengl handle
		/// </summary>
		/// <returns></returns>
		VERTEX_BUFFER_HANDLE get_handle() const;
		void update(const Byte* data);
	protected:

	private:
		void create();
		void invalidate();
	private:
		VERTEX_BUFFER_HANDLE Handle;
		DEVICE Device;
	};


}