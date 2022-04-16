#include "VertexUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	unsigned int VertexUtils::get_data_type_size(const VertexElementDataType type)
	{
		switch (type)
		{
			case DopeEngine::VertexElementDataType::Float:
				return 4;
				break;
			case DopeEngine::VertexElementDataType::Float2:
				return 8;
				break;
			case DopeEngine::VertexElementDataType::Float3:
				return 12;
				break;
			case DopeEngine::VertexElementDataType::Float4:
				return 16;
				break;
			case DopeEngine::VertexElementDataType::Mat3:
				return 36;
				break;
			case DopeEngine::VertexElementDataType::Mat4:
				return 64;
				break;
			default:
				ASSERT(false, "OpenGLVertexUtils", "Invalid VertexElementDataType, cannot get the single component size");
				break;
		}
	}
}