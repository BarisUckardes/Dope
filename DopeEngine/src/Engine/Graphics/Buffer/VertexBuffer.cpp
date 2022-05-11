#include "VertexBuffer.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	
	VertexBuffer::VertexBuffer(const BufferDescription& desc) : GraphicsBuffer(desc)
	{
		PerVertexSize = desc.PerItemSize;
		VertexCapacity = desc.AllocatedSize / desc.PerItemSize;
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