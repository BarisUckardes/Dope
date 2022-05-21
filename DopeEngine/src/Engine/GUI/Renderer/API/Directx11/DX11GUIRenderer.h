#pragma once
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEngine
{
	/// <summary>
	/// Directx11 implementation of a GUIRenderer
	/// </summary>
	class DOPE_ENGINE_API DX11GUIRenderer : public GUIRenderer
	{
	public:
		DX11GUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device);
		~DX11GUIRenderer() = default;

		virtual GraphicsAPIType get_api_type() const override;
	protected:
		virtual void begin_rendering_impl() override;
		virtual void render_impl(const GraphicsCommandBuffer* cmdBuffer) override;
	};


}