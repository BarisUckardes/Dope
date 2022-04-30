#include "DX12PipelineUtils.h"
#include <Engine/Core/Assert.h>


namespace DopeEngine
{
	D3D12_CULL_MODE DX12PipelineUtils::get_dx12_cull_mode(const FaceCullMode mode)
	{
		switch (mode)
		{
			case DopeEngine::FaceCullMode::Front:
				return D3D12_CULL_MODE_FRONT;
				break;
			case DopeEngine::FaceCullMode::Back:
				return D3D12_CULL_MODE_BACK;
				break;
			case DopeEngine::FaceCullMode::FrontAndBack:
				return (D3D12_CULL_MODE)((int)D3D12_CULL_MODE_FRONT | (int)D3D12_CULL_MODE_FRONT);
				break;
			case DopeEngine::FaceCullMode::DontCull:
				return D3D12_CULL_MODE_NONE;
				break;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid FaceCullMode, cannot create D3D12_CULL_MODE");
				break;
		}
	}
	D3D12_FILL_MODE DX12PipelineUtils::get_dx12_fill_mode(const PolygonFillMode mode)
	{
		switch (mode)
		{
			case DopeEngine::PolygonFillMode::Point:
				return D3D12_FILL_MODE_WIREFRAME;
				break;
			case DopeEngine::PolygonFillMode::Line:
				return D3D12_FILL_MODE_WIREFRAME;
				break;
			case DopeEngine::PolygonFillMode::Fill:
				return D3D12_FILL_MODE_SOLID;
				break;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid PolygonFillMode, cannot create D3D12_FILL_MODE");
				break;
		}
	}
	D3D12_PRIMITIVE_TOPOLOGY DX12PipelineUtils::get_dx12_primitives(const PrimitiveTopology primitives)
	{
		switch (primitives)
		{
			case DopeEngine::PrimitiveTopology::Points:
				return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case DopeEngine::PrimitiveTopology::Lines:
				return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case DopeEngine::PrimitiveTopology::Triangles:
				return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			case DopeEngine::PrimitiveTopology::Patches:
				return D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;
				break;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid PrimitiveTopology, cannot create D3D12_PRIMITIVE_TOPOLOGY");
				break;
		}
	}
	D3D12_PRIMITIVE_TOPOLOGY_TYPE DX12PipelineUtils::get_dx12_primitive_type(const PrimitiveTopology primitives)
	{
		switch (primitives)
		{
			case DopeEngine::PrimitiveTopology::Points:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
				break;
			case DopeEngine::PrimitiveTopology::Lines:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				break;
			case DopeEngine::PrimitiveTopology::Triangles:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				break;
			case DopeEngine::PrimitiveTopology::Patches:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
				break;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid PrimitiveTopologyType, cannot create D3D12_PRIMITIVE_TOPOLOGY_TYPE");
				break;
		}
	}
}