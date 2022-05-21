#pragma once
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEngine
{
	/// <summary>
	/// OpenGL implementation of a GUIRenderer
	/// </summary>
	class DOPE_ENGINE_API OpenGLGUIRenderer : public GUIRenderer
	{
	public:
		OpenGLGUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags);
		~OpenGLGUIRenderer() = default;

		virtual GraphicsAPIType get_api_type() const override;
	protected:
		virtual void begin_rendering_impl() override;
		virtual void render_impl(const GraphicsCommandBuffer* cmdbuffer) override;
	};


}