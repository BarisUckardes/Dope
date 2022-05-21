#pragma once
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEngine
{
	/// <summary>
	/// Directx12 implementation of a GUIRenderer
	/// </summary>
	class DX12GUIRenderer : public GUIRenderer
	{
	public:
		DX12GUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device);
		~DX12GUIRenderer() = default;

		virtual GraphicsAPIType get_api_type() const override;
	protected:
		virtual void begin_rendering_impl() override;
		virtual void render_impl(CommandBuffer* cmdBuffer) override;
	};


}