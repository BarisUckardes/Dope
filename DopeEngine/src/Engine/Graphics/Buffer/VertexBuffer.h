#pragma once
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Graphics/Buffer/VertexElementDataType.h>
#include <Engine/Graphics/Buffer/VertexLayoutDescription.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic vertex buffer abstraction class
	/// </summary>
	struct DOPE_ENGINE_API VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const VertexLayoutDescription& layoutDescription);
		virtual ~VertexBuffer() = default;

		/// <summary>
		/// Returns a reference to the vertex layout
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const VertexLayoutDescription& get_layout_fast() const;

		/// <summary>
		/// Returns a copy of the vertex layout
		/// </summary>
		/// <returns></returns>
		FORCEINLINE VertexLayoutDescription get_layout_slow() const;

		/// <summary>
		/// Returns the index buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_vertex_count() const;

		/// <summary>
		/// Allocates anew vertexes
		/// </summary>
		/// <param name="vertexCount"></param>
		void allocate(const unsigned long vertexCount) ;
		
		/// <summary>
		/// Updates the region of this vertex buffer
		/// </summary>
		/// <param name="data"></param>
		void update(const Byte* data);

		/// <summary>
		/// Initializes the buffer layout of this vertex buffer
		/// </summary>
		virtual void initialize_vertex_buffer_layout() = 0;
	protected:
		virtual void allocate_impl(unsigned int vertexCount) = 0;
		virtual void update_impl(const Byte* data) = 0;
		
	private:
		void calculate_diagnostics();
	private:
		VertexLayoutDescription Layout;
		unsigned long VertexCount;
	};
}