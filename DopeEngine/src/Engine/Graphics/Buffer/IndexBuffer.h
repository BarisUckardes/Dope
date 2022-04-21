#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic index buffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const unsigned int elementSize,const unsigned long allocatedSize);
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Returns the index count
		/// </summary>
		/// <returns></returns>
		 unsigned long get_index_capacity() const;

		/// <summary>
		/// Returns the single element size
		/// </summary>
		/// <returns></returns>
		 unsigned int get_element_size() const;
	private:
		unsigned int ElementSize;
		unsigned long IndexCapacity;
	};


}