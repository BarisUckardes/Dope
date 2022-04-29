#include "DX12VertexBuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
    DX12VertexBuffer::DX12VertexBuffer(const unsigned long allocatedSize, const unsigned int perVertexSize, DX12GraphicsDevice* device) : VertexBuffer(perVertexSize,allocatedSize)
    {
        create(device);
    }
    DX12VertexBuffer::~DX12VertexBuffer()
    {

    }
    DXPTR<ID3D12Resource> DX12VertexBuffer::get_dx12_vertex_buffer() const
    {
        return Buffer;
    }
    void DX12VertexBuffer::create(DX12GraphicsDevice* device)
    {
        /*
        * Create heap properties
        */
        D3D12_HEAP_PROPERTIES heapProps = {};
        heapProps.Type = D3D12_HEAP_TYPE_CUSTOM;
        heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
        heapProps.CreationNodeMask = 0;
        heapProps.VisibleNodeMask = 0;
        heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;


        /*
        * Create resource desc
        */
        D3D12_RESOURCE_DESC desc = {};
        desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        desc.Format = DXGI_FORMAT_UNKNOWN;
        desc.MipLevels = 1;
        desc.Alignment = 0;
        desc.DepthOrArraySize = 1;
        desc.Flags = D3D12_RESOURCE_FLAG_NONE;
        desc.Height = 1;
        desc.Width = get_allocated_size();
        desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;

        /*
        * Create commited resource
        */
        HRESULT createResourceHR = device->get_dx12_device()->CreateCommittedResource(&heapProps,
            D3D12_HEAP_FLAG_NONE,
            &desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(Buffer.GetAddressOf())
            );

        /*
        * Validate creation
        */
        ASSERT(SUCCEEDED(createResourceHR), "DX12VertexBuffer", "Vertex buffer creation failed!");
    }
}