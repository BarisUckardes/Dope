#pragma once
#include <Engine/Graphics/Vertex/VertexElementDataType.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLVertexUtils
	{
	public:
		OpenGLVertexUtils() = delete;
		~OpenGLVertexUtils() = delete;

		 static VERTEX_DATA_TYPE get_data_type(const VertexElementDataType type);
		 static unsigned int get_component_count(const VertexElementDataType type);
	};


}