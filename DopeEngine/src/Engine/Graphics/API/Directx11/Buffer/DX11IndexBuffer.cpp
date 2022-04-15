#include "DX11IndexBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
namespace DopeEngine
{
	DX11IndexBuffer::DX11IndexBuffer(const unsigned long range, const unsigned int elementSize, const unsigned long allocatedSize, DX11GraphicsDevice* device) : IndexBuffer(range,elementSize,allocatedSize)
	{
		create(device);
	}
	DX11IndexBuffer::~DX11IndexBuffer()
	{

	}
	ID3D11Buffer* DX11IndexBuffer::get_dx11_buffer() const
	{
		return Buffer;
	}
	void DX11IndexBuffer::create(DX11GraphicsDevice* device)
	{
		/*
		* Create buffer desc
		*/
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = get_allocated_size();
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;

		/*
		* Create init subresource data
		*/
		D3D11_SUBRESOURCE_DATA subInitData;
		subInitData.pSysMem = nullptr;
		subInitData.SysMemPitch = 0;
		subInitData.SysMemSlicePitch = 0;

		/*
		* Create index buffer
		*/
		device->get_dx11_device()->CreateBuffer(&bufferDesc, &subInitData, &Buffer);

	}
}