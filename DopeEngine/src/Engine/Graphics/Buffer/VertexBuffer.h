#pragma once
#include <Engine/Graphics/Buffer/GraphicsBuffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic vertex buffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API VertexBuffer : public GraphicsBuffer
	{
	public:
		VertexBuffer(const BufferDescription& desc);
		virtual ~VertexBuffer() = default;

		unsigned long get_vertex_capacity() const;
		unsigned int get_per_vertex_size() const;
	private:
		unsigned long VertexCapacity;
		unsigned int PerVertexSize;
	};
}