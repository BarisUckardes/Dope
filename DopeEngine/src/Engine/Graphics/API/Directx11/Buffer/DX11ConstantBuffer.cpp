#include "DX11ConstantBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
namespace DopeEngine
{
	DX11ConstantBuffer::DX11ConstantBuffer(const BufferDescription& desc, DX11GraphicsDevice* device) : UniformBuffer(desc)
	{
		create(device);
	}
	DX11ConstantBuffer::~DX11ConstantBuffer()
	{

	}
	DXPTR<ID3D11Buffer> DX11ConstantBuffer::get_dx11_buffer() const
	{
		return Buffer;
	}
	void DX11ConstantBuffer::create(DX11GraphicsDevice* device)
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = get_allocated_size() + (16-(get_allocated_size()%16));
		bufferDesc.StructureByteStride = get_item_size();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		device->get_dx11_device()->CreateBuffer(&bufferDesc, nullptr, &Buffer);
	}
}