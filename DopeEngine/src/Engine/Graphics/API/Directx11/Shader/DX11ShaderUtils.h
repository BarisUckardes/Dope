#pragma once
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11ShaderUtils
	{
	public:
		DX11ShaderUtils() = delete;
		~DX11ShaderUtils() = delete;

		FORCEINLINE static String get_shader_target_string(const ShaderType type, const unsigned int shaderVer);
	};


}