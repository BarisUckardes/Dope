#pragma once
#include <Engine/Graphics/Vertex/VertexElementDataType.h>

namespace DopeEngine
{
	/// <summary>
	/// Util operations for vertexes
	/// </summary>
	class DOPE_ENGINE_API VertexUtils
	{
	public:
		VertexUtils() = delete;
		~VertexUtils() = delete;

		/// <summary>
		/// Returns the vertex element size in bytes
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		static unsigned int get_data_type_size(const VertexElementDataType type);
	};
}