#include "Buffer.h"


namespace DopeEngine
{
	Buffer::Buffer(const BufferDescription& description) : DeviceObject(DeviceObjectType::Buffer)
	{
		Type = description.Type;
		AllocatedSize = description.AllocatedSize;
		ItemSize = description.PerItemSize;
		Name = description.Name;
	}
	BufferType Buffer::get_buffer_type() const
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
	unsigned int Buffer::get_item_size() const
	{
		return ItemSize;
	}
}