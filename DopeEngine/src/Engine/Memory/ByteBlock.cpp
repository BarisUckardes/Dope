#include "ByteBlock.h"

namespace DopeEngine
{
	ByteBlock::ByteBlock(const ByteBlock& block, unsigned long startIndex, unsigned long endIndex)
	{
		const unsigned long sizeDif = endIndex - startIndex;

		Byte* bytes = new Byte[sizeDif];

		Memory::memory_copy(block.get_block_data_ptr(), block.get_block_data_ptr(startIndex), sizeDif);

		Block = bytes;
		Size = sizeDif;
	}

	ByteBlock::ByteBlock(void* dataPtr, unsigned long size)
	{
		Byte* bytes = new Byte[size];

		Memory::memory_copy(bytes, dataPtr, size);

		Block = bytes;
		Size = size;
	}

	ByteBlock::ByteBlock(const ByteBlock& block)
	{
		Byte* bytes = new Byte[block.Size];

		Memory::memory_copy(bytes, block.Block, block.Size);

		Block = bytes;
		Size = block.Size;
	}

	ByteBlock::ByteBlock()
	{
		Block = nullptr;
		Size = 0;
	}

	ByteBlock::~ByteBlock()
	{
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
		Byte* bytes = new Byte[block.Size];

		Memory::memory_copy(bytes, block.Block, block.Size);

		Block = bytes;
		Size = block.Size;

		return *this;
	}
}