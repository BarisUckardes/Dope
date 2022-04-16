#pragma once
#include <Engine/Graphics/Vertex/VertexElementDataType.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VertexUtils
	{
	public:
		VertexUtils() = delete;
		~VertexUtils() = delete;

		FORCEINLINE static unsigned int get_data_type_size(const VertexElementDataType);
	};
}