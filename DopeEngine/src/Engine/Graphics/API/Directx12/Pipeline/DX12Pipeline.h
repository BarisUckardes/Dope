#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Pipeline/Pipeline.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12Pipeline : public Pipeline
	{
	public:
		DX12Pipeline(const PipelineDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12Pipeline() final override;

	private:
		void _create_pipeline(const PipelineDescription& desc, DX12GraphicsDevice* device);
	private:
		ID3D12RootSignature* RootSignature;
		ID3D12PipelineState* PSO;
	};
}