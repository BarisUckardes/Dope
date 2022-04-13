#pragma once
#include <Engine/Graphics/Vertex/VertexLayout.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLVertexLayout final : public VertexLayout
	{
	public:
		OpenGLVertexLayout(const VertexLayoutDescription& description,DEVICE device);
		virtual ~OpenGLVertexLayout() final override;

		/// <summary>
		/// Returns vertex array handle
		/// </summary>
		/// <returns></returns>
		FORCEINLINE VERTEX_LAYOUT_HANDLE get_handle() const;
		virtual void create_layout() final override;
	private:
		void create();
		void invalidate();
	private:
		VERTEX_LAYOUT_HANDLE Handle;
		DEVICE Device;
	};


}