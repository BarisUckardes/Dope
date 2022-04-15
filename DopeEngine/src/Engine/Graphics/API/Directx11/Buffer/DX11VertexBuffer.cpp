#include "DX11VertexBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>

namespace DopeEngine
{
	DX11VertexBuffer::DX11VertexBuffer(DX11GraphicsDevice* device,const unsigned long allocatedSize, const unsigned int perVertexSize) : VertexBuffer(perVertexSize, allocatedSize)
	{
		create(device);
	}
	DX11VertexBuffer::~DX11VertexBuffer()
	{

	}
	ID3D11Buffer* DX11VertexBuffer::get_dx11_buffer() const
	{
		return Buffer;
	}
	void DX11VertexBuffer::create(DX11GraphicsDevice* device)
	{
		
		/*
		* Create buffer desc
		*/
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = get_allocated_size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;

		/*
		* Create sub resource data to fill
		*/
		D3D11_SUBRESOURCE_DATA subInitData;
		subInitData.pSysMem = nullptr;
		subInitData.SysMemPitch = 0;
		subInitData.SysMemSlicePitch = 0;

		/*
		* Create vertex buffer
		*/
		device->get_dx11_device()->CreateBuffer(&bufferDesc, &subInitData, &Buffer);
	}
}