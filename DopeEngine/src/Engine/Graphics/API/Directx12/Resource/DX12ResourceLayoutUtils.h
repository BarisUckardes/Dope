#pragma once
#include <Engine/Graphics/Resource/ResourceSlotDesc.h>
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ResourceLayoutUtils
	{
	public:
		DX12ResourceLayoutUtils() = delete;
		~DX12ResourceLayoutUtils() = delete;

		static D3D12_ROOT_PARAMETER_TYPE get_dx12_root_parameter_type(const ResourceType type);
	};
}