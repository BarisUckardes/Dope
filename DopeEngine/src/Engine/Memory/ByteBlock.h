#pragma once
#include <Engine/Memory/Memory.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API ByteBlock
	{
	public:
		ByteBlock(const ByteBlock& block, unsigned long startIndex, unsigned long endIndex);
		ByteBlock(const ByteBlock& other);
		ByteBlock(void* dataPtr, unsigned long size);
		ByteBlock();
		~ByteBlock();

		FORCEINLINE Byte* get_block_data_ptr(const unsigned long offset = 0) const;
		FORCEINLINE unsigned long get_size() const;

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