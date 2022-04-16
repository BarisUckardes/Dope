#include "OpenGLVertexUtils.h"
#include <GLAD/glad.h>
#include <Engine/Core/Assert.h>

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
	unsigned int OpenGLVertexUtils::get_component_count(const VertexElementDataType type)
	{
		switch (type)
		{
			case DopeEngine::VertexElementDataType::Float:
				return 1;
				break;
			case DopeEngine::VertexElementDataType::Float2:
				return 2;
				break;
			case DopeEngine::VertexElementDataType::Float3:
				return 3;
				break;
			case DopeEngine::VertexElementDataType::Float4:
				return 4;
				break;
			case DopeEngine::VertexElementDataType::Mat3:
				return 3;
				break;
			case DopeEngine::VertexElementDataType::Mat4:
				return 4;
				break;
			default:
				ASSERT(false, "OpenGLVertexUtils", "Invalid VertexElementDataType, cannot get the component type");
				break;
		}
	}
	

}