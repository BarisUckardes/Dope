#pragma once
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic vertex buffer abstraction class
	/// </summary>
	struct DOPE_ENGINE_API VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const unsigned int perVertexSize,const unsigned long allocatedSize);
		virtual ~VertexBuffer() = default;

		/// <summary>
		/// Returns the index buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_vertex_capacity() const;

		/// <summary>
		/// Returns the single vertex size in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_per_vertex_size() const;
	private:
		unsigned long VertexCapacity;
		unsigned int PerVertexSize;
	};
}