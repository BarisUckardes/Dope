#include "IndexBuffer.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{

	IndexBuffer::IndexBuffer(const BufferDescription& desc) : Buffer(desc)
	{
		ElementSize = desc.PerItemSize;
		IndexCapacity = desc.AllocatedSize / desc.PerItemSize;
	}
	unsigned long IndexBuffer::get_index_capacity() const
	{
		return IndexCapacity;
	}
}