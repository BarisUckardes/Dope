#include "DX11VertexBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	DX11VertexBuffer::DX11VertexBuffer(const BufferDescription& desc,DX11GraphicsDevice* device) : VertexBuffer(desc)
	{
		create(device);
	}
	DX11VertexBuffer::~DX11VertexBuffer()
	{

	}
	DXPTR<ID3D11Buffer> DX11VertexBuffer::get_dx11_buffer() const
	{
		return Buffer;
	}
	void DX11VertexBuffer::create(DX11GraphicsDevice* device)
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = get_allocated_size();
		bufferDesc.StructureByteStride = get_per_vertex_size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		device->get_dx11_device()->CreateBuffer(&bufferDesc,nullptr, &Buffer);
	}
}