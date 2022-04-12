#pragma once
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLShaderUtils
	{
	public:
		OpenGLShaderUtils() = delete;
		~OpenGLShaderUtils() = delete;

		static FORCEINLINE SHADER_TYPE get_type(const ShaderType type);
	};


}