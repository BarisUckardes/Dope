#pragma once
#include <Engine/Graphics/Pipeline/PipelineDescription.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12PipelineUtils
	{
	public:
		DX12PipelineUtils() = delete;
		~DX12PipelineUtils() = delete;


		static D3D12_CULL_MODE get_dx12_cull_mode(const FaceCullMode mode);
		static D3D12_FILL_MODE get_dx12_fill_mode(const PolygonFillMode mode);
		static D3D12_PRIMITIVE_TOPOLOGY_TYPE get_dx12_primitives(const PrimitiveTopology primitives);
	};


}