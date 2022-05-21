#pragma once
#include <Engine/Memory/Memory.h>

namespace DopeEngine
{
	/// <summary>
	/// Represents a block of bytes
	/// </summary>
	class DOPE_ENGINE_API ByteBlock
	{
	public:
		ByteBlock(const ByteBlock& block, unsigned long startIndex, unsigned long endIndex);
		ByteBlock(const ByteBlock& other);
		ByteBlock(void* dataPtr, unsigned long size);
		ByteBlock();
		~ByteBlock();

		/// <summary>
		/// Returns a pointer with an offset to data
		/// </summary>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE Byte* get_block_data_ptr(const unsigned long offset = 0) const;

		/// <summary>
		/// Returns how many bytes this block contains
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_size() const;

		/// <summary>
		/// Converts the block to a specified type with an offset
		/// </summary>
		/// <typeparam name="TObject"></typeparam>
		/// <param name="offset"></param>
		/// <returns></returns>
		template<typename TObject>
		TObject to(const unsigned long offset = 0) const;

		ByteBlock& operator=(const ByteBlock& block);
	private:
		Byte* Block;
		unsigned long Size;
	};



	template<typename TObject>
	inline TObject ByteBlock::to(const unsigned long offset) const
	{
		return *(TObject*)(Block + offset);
	}


}