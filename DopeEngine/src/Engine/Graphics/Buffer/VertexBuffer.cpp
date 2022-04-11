#include "VertexBuffer.h"

namespace DopeEngine
{
	
	VertexBuffer::VertexBuffer(const unsigned int perVertexSize, const unsigned long allocatedSize) : Buffer(BufferType::VertexBuffer,allocatedSize)
	{
		PerVertexSize = perVertexSize;
		VertexCapacity = allocatedSize / perVertexSize;
	}

	unsigned long VertexBuffer::get_vertex_capacity() const
	{
		return VertexCapacity;
	}

	unsigned int VertexBuffer::get_per_vertex_size() const
	{
		return PerVertexSize;
	}


}