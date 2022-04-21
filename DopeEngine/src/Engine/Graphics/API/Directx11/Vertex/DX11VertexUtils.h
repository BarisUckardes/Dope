#pragma once
#include <Engine/Graphics/Vertex/VertexElementDataType.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11VertexUtils
	{
	public:
		DX11VertexUtils() = delete;
		~DX11VertexUtils() = delete;

		static  DXGI_FORMAT get_format(const VertexElementDataType type);
	};


}