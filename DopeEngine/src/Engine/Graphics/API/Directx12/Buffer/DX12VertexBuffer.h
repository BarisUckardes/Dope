#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Buffer/VertexBuffer.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12VertexBuffer : public VertexBuffer
	{
	public:
		DX12VertexBuffer(const unsigned long allocatedSize, const unsigned int perVertexSize, DX12GraphicsDevice* device);
		virtual ~DX12VertexBuffer() final override;
	};


}