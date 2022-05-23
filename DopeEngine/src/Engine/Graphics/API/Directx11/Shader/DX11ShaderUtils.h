#pragma once
#include <Engine/Graphics/Shader/ShaderStage.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11ShaderUtils
	{
	public:
		DX11ShaderUtils() = delete;
		~DX11ShaderUtils() = delete;

		 static String get_shader_target_string(const ShaderStage type, const unsigned int majorVersion,const unsigned int minorVersion);
	};


}