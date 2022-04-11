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
		IndexBuffer(const unsigned long range,const unsigned int elementSize,const unsigned long allocatedSize);
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Returns the index count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_index_capacity() const;

		/// <summary>
		/// Returns the max count indexes this buffer can get
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_range() const;

		/// <summary>
		/// Returns the single element size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_element_size() const;
	private:
		unsigned long Range;
		unsigned int ElementSize;
		unsigned long IndexCapacity;
	};


}