#include "DX12ResourceLayoutUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	D3D12_ROOT_PARAMETER_TYPE DX12ResourceLayoutUtils::get_dx12_root_parameter_type(const ResourceType type)
	{
		switch (type)
		{
			case DopeEngine::ResourceType::UniformBuffer:
				return D3D12_ROOT_PARAMETER_TYPE_SRV;
				break;
			case DopeEngine::ResourceType::Texture:
				return D3D12_ROOT_PARAMETER_TYPE_SRV;
				break;
			case DopeEngine::ResourceType::Undefined:
			default:
				ASSERT(false,"DX12ResourceLayoutUtils", "Invalid ResourceType, cannot produce and D3D12_ROOT_PARAMETER_TYPE");
				break;
		}
	}

}

