#pragma once
#include <Engine/Graphics/Buffer/UniformBuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DX11GraphicsDevice;

	class DOPE_ENGINE_API DX11ConstantBuffer final : public UniformBuffer
	{
	public:
		DX11ConstantBuffer(const BufferDescription& desc,DX11GraphicsDevice* device);
		virtual ~DX11ConstantBuffer() final override;

		FORCEINLINE ID3D11Buffer* get_dx11_buffer() const;
	private:
		void create(DX11GraphicsDevice* device);
	private:
		ID3D11Buffer* Buffer;
	};
}