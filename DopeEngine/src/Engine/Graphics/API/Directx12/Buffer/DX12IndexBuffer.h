#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Buffer/IndexBuffer.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12IndexBuffer : public IndexBuffer
	{
	public:
		DX12IndexBuffer(const unsigned int elementSize, const unsigned long allocatedSize, DX12GraphicsDevice* device);
		virtual ~DX12IndexBuffer() final override;

		FORCEINLINE DXPTR<ID3D12Resource> get_dx12_index_buffer() const;
	private:
		void create(DX12GraphicsDevice* device);
	private:
		DXPTR<ID3D12Resource> Buffer;
	};

}