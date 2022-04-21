#include "DX12VertexBuffer.h"

namespace DopeEngine
{
    DX12VertexBuffer::DX12VertexBuffer(const unsigned long allocatedSize, const unsigned int perVertexSize, DX12GraphicsDevice* device) : VertexBuffer(perVertexSize,allocatedSize)
    {
    }
    DX12VertexBuffer::~DX12VertexBuffer()
    {
    }
}