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

		VERTEX_DATA_TYPE static get_data_type(const VertexElementDataType type);
	};


}