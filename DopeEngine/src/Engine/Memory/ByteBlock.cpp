#include "ByteBlock.h"

namespace DopeEngine
{
	ByteBlock::ByteBlock(const ByteBlock& block, unsigned long startIndex, unsigned long endIndex)
	{
		/*
		* Get size
		*/
		const unsigned long sizeDif = endIndex - startIndex;

		/*
		* Create new byteblock
		*/
		Byte* bytes = new Byte[sizeDif];

		/*
		* Copy contents
		*/
		Memory::memory_copy(block.get_block_data_ptr(), block.get_block_data_ptr(startIndex), sizeDif);

		/*
		* Initialize
		*/
		Block = bytes;
		Size = sizeDif;

	}

	ByteBlock::ByteBlock(void* dataPtr, unsigned long size)
	{
		/*
		* Create new byte block
		*/
		Byte* bytes = new Byte[size];

		/*
		* Copy contents
		*/
		Memory::memory_copy(bytes, dataPtr, size);

		/*
		* Initialize
		*/
		Block = bytes;
		Size = size;
	}

	ByteBlock::ByteBlock(const ByteBlock& block)
	{
		/*
		* Create new byte block
		*/
		Byte* bytes = new Byte[block.Size];

		/*
		* Copy contens
		*/
		Memory::memory_copy(bytes, block.Block, block.Size);

		/*
		* Initialize
		*/
		Block = bytes;
		Size = block.Size;
	}

	ByteBlock::ByteBlock()
	{
		/*
		* Initialize default
		*/
		Block = nullptr;
		Size = 0;
	}

	ByteBlock::~ByteBlock()
	{
		/*
		* Validate and clear data
		*/
		if (Block != nullptr)
			delete[] Block;
		Size = 0;
	}

	Byte* ByteBlock::get_block_data_ptr(const unsigned long offset) const
	{
		return (Block + offset);
	}

	unsigned long ByteBlock::get_size() const
	{
		return Size;
	}
	ByteBlock& ByteBlock::operator=(const ByteBlock& block)
	{
		/*
		* Create new byte block
		*/
		Byte* bytes = new Byte[block.Size];

		/*
		* Copy contens
		*/
		Memory::memory_copy(bytes, block.Block, block.Size);

		/*
		* Initialize
		*/
		Block = bytes;
		Size = block.Size;

		return *this;
	}
}