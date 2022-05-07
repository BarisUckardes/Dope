#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/RenderPass/RenderPass.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12RenderPass : public RenderPass
	{
	public:
		DX12RenderPass(const RenderPassDesc& desc, DX12GraphicsDevice* device);
		virtual ~DX12RenderPass() final override;


		DXPTR<ID3D12RootSignature> get_dx12_root_signature() const;
		DXPTR<ID3D12PipelineState> get_dx12_pso() const;
		D3D12_VIEWPORT get_dx12_viewport() const;
		D3D12_RECT get_dx12_scissors() const;
	private:
		void _create_pipeline(const RenderPassDesc& desc, DX12GraphicsDevice* device);
	private:
		DXPTR<ID3D12RootSignature> RootSignature;
		DXPTR<ID3D12PipelineState> Pso;
		D3D12_VIEWPORT Viewport;
		D3D12_RECT ScissorRect;
	};
}