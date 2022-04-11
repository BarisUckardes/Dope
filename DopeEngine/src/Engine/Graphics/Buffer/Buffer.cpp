#include "Buffer.h"

namespace DopeEngine
{
	Buffer::Buffer(const BufferType type,const unsigned long allocatedSize)
	{
		Type = type;
		AllocatedSize = allocatedSize;
	}
	BufferType Buffer::get_type() const
	{
		return Type;
	}
	unsigned long Buffer::get_allocated_size() const
	{
		return AllocatedSize;
	}
	void Buffer::update(const Byte* data)
	{
		/*
		* Call impl
		*/
		update_impl(data);

	}
}