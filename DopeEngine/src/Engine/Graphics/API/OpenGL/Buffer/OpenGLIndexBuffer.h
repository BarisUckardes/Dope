#pragma once
#include <Engine/Graphics/Buffer/IndexBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	/// <summary>
	/// OpenGL implementation of a index buffer
	/// </summary>
	class DOPE_ENGINE_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const unsigned long range, const unsigned int elementSize, const unsigned long allocatedSize,DEVICE device);
		virtual ~OpenGLIndexBuffer() final override;

		/// <summary>
		/// Returns opengl index buffer handle
		/// </summary>
		/// <returns></returns>
		FORCEINLINE INDEX_BUFFER_HANDLE get_handle() const;
		void update(const Byte* data);
	private:
		void create();
		void invalidate();
	private:
		INDEX_BUFFER_HANDLE Handle;
		DEVICE Device;
	};

}
