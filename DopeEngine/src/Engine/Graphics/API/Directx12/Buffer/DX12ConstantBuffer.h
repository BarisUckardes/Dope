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
	};


}