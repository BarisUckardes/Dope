#include "IndexBuffer.h"

namespace DopeEngine
{

	IndexBuffer::IndexBuffer(const unsigned long range, const unsigned int elementSize, const unsigned long allocatedSize) : Buffer(BufferType::IndexBuffer,allocatedSize)
	{
		Range = range;
		ElementSize = elementSize;
		IndexCapacity = allocatedSize / elementSize;
	}
	unsigned long IndexBuffer::get_index_capacity() const
	{
		return IndexCapacity;
	}
	unsigned long IndexBuffer::get_range() const
	{
		return Range;
	}
	unsigned int IndexBuffer::get_element_size() const
	{
		return ElementSize;
	}
}