#include "DX12ShaderUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	D3D12_SHADER_VISIBILITY DX12ShaderUtils::get_dx12_shader_visibility(ShaderStage type)
	{
		switch (type)
		{
			case DopeEngine::ShaderStage::Vertex:
				return D3D12_SHADER_VISIBILITY_VERTEX;
				break;
			case DopeEngine::ShaderStage::Fragment:
				return D3D12_SHADER_VISIBILITY_PIXEL;
				break;
			case DopeEngine::ShaderStage::Geometry:
				return D3D12_SHADER_VISIBILITY_GEOMETRY;
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				break;
			case DopeEngine::ShaderStage::Compute:
				break;
			case DopeEngine::ShaderStage::Undefined:
				break;
			default:
				ASSERT(false, "DX12ShaderUtils", "Invalid ShaderStage, cannot produce D3D12_SHADER_VISIBILITY");
				break;
		}
	}

}