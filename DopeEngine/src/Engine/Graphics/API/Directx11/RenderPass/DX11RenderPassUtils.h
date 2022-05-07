#pragma once
#include <Engine/Graphics/RenderPass/RenderPassDesc.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11RenderPassUtils
	{
	public:
		DX11RenderPassUtils() = delete;
		~DX11RenderPassUtils() = delete;

		 static D3D11_FILL_MODE get_fill_mode(const PolygonFillMode mode);
		 static D3D11_CULL_MODE get_cull_mode(const FaceCullMode mode);
	};


}