#include "OpenGLShaderUtils.h"
#include <GLAD/glad.h>
namespace DopeEngine
{
	SHADER_TYPE OpenGLShaderUtils::get_type(const ShaderStage type)
	{
		switch (type)
		{
			case DopeEngine::ShaderStage::Vertex:
				return GL_VERTEX_SHADER;
				break;
			case DopeEngine::ShaderStage::Fragment:
				return GL_FRAGMENT_SHADER;
				break;
			case DopeEngine::ShaderStage::Geometry:
				return GL_GEOMETRY_SHADER;
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				return GL_TESS_EVALUATION_SHADER;
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				return GL_TESS_CONTROL_SHADER;
				break;
			case DopeEngine::ShaderStage::Compute:
				return GL_COMPUTE_SHADER;
				break;
			default:
				return GL_NONE;
				break;
		}
	}
}