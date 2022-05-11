#include "GraphicsBuffer.h"


namespace DopeEngine
{
	GraphicsBuffer::GraphicsBuffer(const BufferDescription& description) : GraphicsDeviceObject(GraphicsDeviceObjectType::Buffer)
	{
		Type = description.Type;
		AllocatedSize = description.AllocatedSize;
		ItemSize = description.PerItemSize;
		Name = description.Name;
	}
	BufferType GraphicsBuffer::get_buffer_type() const
	{
		return Type;
	}
	String GraphicsBuffer::get_buffer_name() const
	{
		return Name;
	}
	unsigned long GraphicsBuffer::get_allocated_size() const
	{
		return AllocatedSize;
	}
	unsigned int GraphicsBuffer::get_item_size() const
	{
		return ItemSize;
	}
}