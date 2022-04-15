#include "DX11VertexUtils.h"

namespace DopeEngine
{
	DXGI_FORMAT DX11VertexUtils::get_format(const VertexElementDataType type)
	{
		switch (type)
		{
			case DopeEngine::VertexElementDataType::Float:
				return DXGI_FORMAT_R32_FLOAT;
				break;
			case DopeEngine::VertexElementDataType::Float2:
				return DXGI_FORMAT_R32G32_FLOAT;
				break;
			case DopeEngine::VertexElementDataType::Float3:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case DopeEngine::VertexElementDataType::Float4:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			case DopeEngine::VertexElementDataType::Mat3:
				break;
			case DopeEngine::VertexElementDataType::Mat4:
				break;
			default:
				break;
		}
	}
}