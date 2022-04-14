#include "Buffer.h"


namespace DopeEngine
{
	Buffer::Buffer(const BufferDescription& description) : DeviceObject(DeviceObjectType::Buffer)
	{
		Type = description.Type;
		AllocatedSize = description.AllocatedSize;
		Name = description.Name;
	}
	BufferType Buffer::get_type() const
	{
		return Type;
	}
	String Buffer::get_buffer_name() const
	{
		return Name;
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