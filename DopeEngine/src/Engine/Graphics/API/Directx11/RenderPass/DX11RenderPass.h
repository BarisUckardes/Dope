#pragma once
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11RenderPass : public RenderPass
	{
	public:
		DX11RenderPass(const RenderPassDesc& desc, DX11GraphicsDevice* device);
		virtual ~DX11RenderPass() final override;

		 DXPTR<ID3D11InputLayout> get_dx11_input_layout() const;
		 DXPTR<ID3D11RasterizerState> get_dx11_rasterizer_state() const;
		 DXPTR<ID3D11DepthStencilState> get_dx11_depth_stencil_state() const;
		 DXPTR<ID3D11BlendState> get_dx1_get_blend_state() const;
	private:
		void create(const RenderPassDesc& desc, DX11GraphicsDevice* device);
	private:
		DXPTR<ID3D11InputLayout> InputLayout;
		DXPTR<ID3D11RasterizerState> RasterizerState;
		DXPTR<ID3D11DepthStencilState> DepthStencilState;
		DXPTR<ID3D11BlendState> BlendState;
	};


}