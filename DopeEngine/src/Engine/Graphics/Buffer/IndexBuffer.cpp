#include "IndexBuffer.h"

namespace DopeEngine
{
	IndexBuffer::IndexBuffer(const IndexBufferDescription& description) : Buffer(BufferType::IndexBuffer)
	{
		Description = description;
		IndexCount = 0;
	}
	IndexBufferDescription IndexBuffer::get_description() const
	{
		return Description;
	}
	unsigned long IndexBuffer::get_index_count() const
	{
		return IndexCount;
	}
	void IndexBuffer::allocate(unsigned long count)
	{
		/*
		* Call impl
		*/
		allocate_impl(count);

		/*
		* Call diagnostics
		*/
		calculate_diagnostics();
	}
	void IndexBuffer::update(const Byte* data)
	{
		/*
		* Call update impl
		*/
		update_impl(data);
	}
	void IndexBuffer::calculate_diagnostics()
	{
		/*
		* Calculate size
		*/
		const unsigned long size = IndexCount * Description.Padding;

		/*
		* Set allocated size
		*/
		set_allocated_size(size);
	}
}