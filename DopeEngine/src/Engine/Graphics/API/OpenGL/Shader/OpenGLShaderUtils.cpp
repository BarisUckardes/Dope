#include "OpenGLShaderUtils.h"
#include <GLAD/glad.h>
namespace DopeEngine
{
	SHADER_TYPE OpenGLShaderUtils::get_type(const ShaderType type)
	{
		switch (type)
		{
			case DopeEngine::ShaderType::Vertex:
				return GL_VERTEX_SHADER;
				break;
			case DopeEngine::ShaderType::Fragment:
				return GL_FRAGMENT_SHADER;
				break;
			case DopeEngine::ShaderType::Geometry:
				return GL_GEOMETRY_SHADER;
				break;
			case DopeEngine::ShaderType::TesellationEval:
				return GL_TESS_EVALUATION_SHADER;
				break;
			case DopeEngine::ShaderType::TesellationControl:
				return GL_TESS_CONTROL_SHADER;
				break;
			case DopeEngine::ShaderType::Compute:
				return GL_COMPUTE_SHADER;
				break;
			default:
				return GL_NONE;
				break;
		}
	}
}