#pragma once
#include <Engine/Graphics/RenderPass/RenderPassDesc.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12RenderPassUtils
	{
	public:
		DX12RenderPassUtils() = delete;
		~DX12RenderPassUtils() = delete;


		static D3D12_CULL_MODE get_dx12_cull_mode(const FaceCullMode mode);
		static D3D12_FILL_MODE get_dx12_fill_mode(const PolygonFillMode mode);
		static D3D12_PRIMITIVE_TOPOLOGY get_dx12_primitives(const PrimitiveTopology primitives);
		static D3D12_PRIMITIVE_TOPOLOGY_TYPE get_dx12_primitive_type(const PrimitiveTopology primitives);
	};


}