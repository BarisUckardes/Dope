#include "DX12IndexBuffer.h"

namespace DopeEngine
{
    DX12IndexBuffer::DX12IndexBuffer(const unsigned int elementSize, const unsigned long allocatedSize, DX12GraphicsDevice* device) : IndexBuffer(elementSize,allocatedSize)
    {
    }
    DX12IndexBuffer::~DX12IndexBuffer()
    {
    }
}