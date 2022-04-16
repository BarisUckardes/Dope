#pragma once
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX11VertexBuffer final : public VertexBuffer
	{
	public:
		DX11VertexBuffer(DX11GraphicsDevice* device,const unsigned long allocatedSize, const unsigned int perVertexSize);
		virtual ~DX11VertexBuffer() final override;

		FORCEINLINE DXPTR<ID3D11Buffer> get_dx11_buffer() const;
	private:
		void create(DX11GraphicsDevice* device);
	private:
		DXPTR<ID3D11Buffer> Buffer;
	};


}