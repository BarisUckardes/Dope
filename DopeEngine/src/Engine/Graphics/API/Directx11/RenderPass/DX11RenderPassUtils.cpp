#include "DX11RenderPassUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
    D3D11_FILL_MODE DX11RenderPassUtils::get_fill_mode(const PolygonFillMode mode)
    {
		switch (mode)
		{
			case DopeEngine::PolygonFillMode::Point:
				return D3D11_FILL_WIREFRAME;
				break;
			case DopeEngine::PolygonFillMode::Line:
				return D3D11_FILL_WIREFRAME;
				break;
			case DopeEngine::PolygonFillMode::Fill:
				return D3D11_FILL_SOLID;
				break;
			default:
				ASSERT(false, "DX11PipelineUtils", "Invalid PolygonFillMode, Cannot create D3D11_FILL_MODE!");
				break;
		}
    }
	D3D11_CULL_MODE DX11RenderPassUtils::get_cull_mode( FaceCullMode mode)
	{
		switch (mode)
		{
			case DopeEngine::FaceCullMode::Front:
				return D3D11_CULL_FRONT;
				break;
			case DopeEngine::FaceCullMode::Back:
				return D3D11_CULL_BACK;
				break;
			case DopeEngine::FaceCullMode::FrontAndBack:
				return D3D11_CULL_BACK;
				break;
			case DopeEngine::FaceCullMode::DontCull:
				return D3D11_CULL_BACK;
				break;
			default:
				ASSERT(false, "DX11PipelineUtils", "Invalid FaceCullMode, Cannot create D3D11_CULL_MODE!");
				break;
		}
	}
}