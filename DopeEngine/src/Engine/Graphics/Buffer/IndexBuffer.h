#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Buffer/GraphicsBuffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic index buffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API IndexBuffer : public GraphicsBuffer
	{
	public:
		IndexBuffer(const BufferDescription& desc);
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Returns the index count
		/// </summary>
		/// <returns></returns>
		unsigned long get_index_capacity() const;

	private:
		unsigned int ElementSize;
		unsigned long IndexCapacity;
	};


}