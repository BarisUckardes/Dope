#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Buffer/VertexBuffer.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12VertexBuffer : public VertexBuffer
	{
	public:
		DX12VertexBuffer(const BufferDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12VertexBuffer() final override;

		DXPTR<ID3D12Resource> get_dx12_vertex_buffer() const;
		const D3D12_VERTEX_BUFFER_VIEW& get_dx12_vertex_buffer_view() const;
	private:
		void create(DX12GraphicsDevice* device);
	private:
		DXPTR<ID3D12Resource> Buffer;
		D3D12_VERTEX_BUFFER_VIEW BufferView;
	};


}