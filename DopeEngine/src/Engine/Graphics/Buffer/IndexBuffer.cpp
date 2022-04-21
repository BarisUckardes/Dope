#include "IndexBuffer.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{

	IndexBuffer::IndexBuffer(const unsigned int elementSize, const unsigned long allocatedSize) : Buffer(BufferDescription("IndexBuffer", BufferType::IndexBuffer, allocatedSize,elementSize))
	{
		ElementSize = elementSize;
		IndexCapacity = allocatedSize / elementSize;
	}
	unsigned long IndexBuffer::get_index_capacity() const
	{
		return IndexCapacity;
	}
	unsigned int IndexBuffer::get_element_size() const
	{
		return ElementSize;
	}
}