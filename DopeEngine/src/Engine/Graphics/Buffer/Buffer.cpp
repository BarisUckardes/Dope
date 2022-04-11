#include "Buffer.h"

namespace DopeEngine
{
	Buffer::Buffer(const BufferType type)
	{
		Type = type;
		AllocatedSize = 0;
	}
	BufferType Buffer::get_type() const
	{
		return Type;
	}
	unsigned long Buffer::get_allocated_size() const
	{
		return AllocatedSize;
	}
	void Buffer::set_allocated_size(const unsigned long size)
	{
		AllocatedSize = size;
	}
}