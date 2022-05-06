#include "DX12ShaderUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	D3D12_SHADER_VISIBILITY DX12ShaderUtils::get_dx12_shader_visibility(ShaderType type)
	{
		switch (type)
		{
			case DopeEngine::ShaderType::Vertex:
				return D3D12_SHADER_VISIBILITY_VERTEX;
				break;
			case DopeEngine::ShaderType::Fragment:
				return D3D12_SHADER_VISIBILITY_PIXEL;
				break;
			case DopeEngine::ShaderType::Geometry:
				return D3D12_SHADER_VISIBILITY_GEOMETRY;
				break;
			case DopeEngine::ShaderType::TesellationEval:
				break;
			case DopeEngine::ShaderType::TesellationControl:
				break;
			case DopeEngine::ShaderType::Compute:
				break;
			case DopeEngine::ShaderType::Undefined:
				break;
			default:
				ASSERT(false, "DX12ShaderUtils", "Invalid ShaderType, cannot produce D3D12_SHADER_VISIBILITY");
				break;
		}
	}

}