#include "DX12ConstantBuffer.h"

namespace DopeEngine
{
    DX12ConstantBuffer::DX12ConstantBuffer(const BufferDescription& desc, DX12GraphicsDevice* device) : UniformBuffer(desc.Name,desc.AllocatedSize)
    {
    }
    DX12ConstantBuffer::~DX12ConstantBuffer()
    {
    }
}