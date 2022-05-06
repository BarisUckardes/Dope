#pragma once
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic vertex buffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const BufferDescription& desc);
		virtual ~VertexBuffer() = default;

		/// <summary>
		/// Returns the index buffer
		/// </summary>
		/// <returns></returns>
		unsigned long get_vertex_capacity() const;

		/// <summary>
		/// Returns the single vertex size in bytes
		/// </summary>
		/// <returns></returns>
		unsigned int get_per_vertex_size() const;
	private:
		unsigned long VertexCapacity;
		unsigned int PerVertexSize;
	};
}