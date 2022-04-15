#pragma once
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11Pipeline : public Pipeline
	{
	public:
		DX11Pipeline(const PipelineDescription& desc, DX11GraphicsDevice* device);
		virtual ~DX11Pipeline() final override;

		FORCEINLINE ID3D11InputLayout* get_dx11_input_layout() const;
		FORCEINLINE ID3D11RasterizerState* get_dx11_rasterizer_state() const;
		FORCEINLINE ID3D11DepthStencilState* get_dx11_depth_stencil_state() const;
		FORCEINLINE ID3D11BlendState* get_dx1_get_blend_state() const;
	private:
		void create(const PipelineDescription& desc, DX11GraphicsDevice* device);
	private:
		ID3D11InputLayout* InputLayout;
		ID3D11RasterizerState* RasterizerState;
		ID3D11DepthStencilState* DepthStencilState;
		ID3D11BlendState* BlendState;
	};


}