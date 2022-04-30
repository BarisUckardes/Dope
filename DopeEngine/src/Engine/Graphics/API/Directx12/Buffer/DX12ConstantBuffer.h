#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Buffer/UniformBuffer.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ConstantBuffer final : public UniformBuffer
	{
	public:
		DX12ConstantBuffer(const BufferDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12ConstantBuffer() final override;

		DXPTR<ID3D12Resource> get_dx12_constant_buffer() const;
	private:
		void create(DX12GraphicsDevice* device);
	private:
		DXPTR<ID3D12Resource> Buffer;
		D3D12_CONSTANT_BUFFER_VIEW_DESC BufferView;
	};


}