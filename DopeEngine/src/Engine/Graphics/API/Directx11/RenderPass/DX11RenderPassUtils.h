#pragma once
#include <Engine/Graphics/Pipeline/PipelineDescription.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11PipelineUtils
	{
	public:
		DX11PipelineUtils() = delete;
		~DX11PipelineUtils() = delete;

		 static D3D11_FILL_MODE get_fill_mode(const PolygonFillMode mode);
		 static D3D11_CULL_MODE get_cull_mode(const FaceCullMode mode);
	};


}