#pragma once
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ShaderUtils
	{
	public:
		DX12ShaderUtils() = delete;
		~DX12ShaderUtils() = delete;

		static D3D12_SHADER_VISIBILITY get_dx12_shader_visibility(const ShaderType type);
	};
}