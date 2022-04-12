#include "OpenGLVertexUtils.h"
#include <GLAD/glad.h>

namespace DopeEngine
{
	VERTEX_DATA_TYPE OpenGLVertexUtils::get_data_type(const VertexElementDataType type)
	{
		switch (type)
		{
			case DopeEngine::VertexElementDataType::Float:
			case DopeEngine::VertexElementDataType::Float2:
			case DopeEngine::VertexElementDataType::Float3:
			case DopeEngine::VertexElementDataType::Float4:
			case DopeEngine::VertexElementDataType::Mat3:
			case DopeEngine::VertexElementDataType::Mat4:
				return GL_FLOAT;
			default:
				return GL_NONE;
				break;
		}
	}
}