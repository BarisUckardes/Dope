#include "VertexBuffer.h"

namespace DopeEngine
{
	VertexBuffer::VertexBuffer(const VertexLayoutDescription& layoutDescription) : Buffer(BufferType::VertexBuffer)
	{
		/*
		* Initialize
		*/
		Layout = layoutDescription;
		VertexCount = 0;

		/*
		* Run diagnostics
		*/
		calculate_diagnostics();
	}
	const VertexLayoutDescription& VertexBuffer::get_layout_fast() const
	{
		return Layout;
	}
	VertexLayoutDescription VertexBuffer::get_layout_slow() const
	{
		return Layout;
	}
	unsigned long VertexBuffer::get_vertex_count() const
	{
		return VertexCount;
	}
	void VertexBuffer::allocate(const unsigned long vertexCount)
	{
		/*
		* Call impl
		*/
		allocate_impl(vertexCount);

		/*
		* Set and calculate diagnostics
		*/
		VertexCount = vertexCount;
		calculate_diagnostics();
	}
	void VertexBuffer::update(const Byte* data)
	{
		/*
		* Call impl
		*/
		update_impl(data);
	}
	void VertexBuffer::calculate_diagnostics()
	{
		/*
		* Calculate total size
		*/
		const unsigned long size = Layout.get_stride() * VertexCount;

		/*
		* Update buffer's allocated size
		*/
		set_allocated_size(size);
	}
}