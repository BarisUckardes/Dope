#pragma once
#include <Engine/Graphics/Buffer/IndexBuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>

namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11IndexBuffer final : public IndexBuffer
	{
	public:
		DX11IndexBuffer(const unsigned int elementSize, const unsigned long allocatedSize, DX11GraphicsDevice* device);
		virtual ~DX11IndexBuffer() final override;

		 DXPTR<ID3D11Buffer> get_dx11_buffer() const;
	private:
		void create(DX11GraphicsDevice* device);
	private:
		DXPTR<ID3D11Buffer> Buffer;
	};


}