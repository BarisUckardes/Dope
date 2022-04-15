#pragma once
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>

namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11Framebuffer final : public Framebuffer
	{
	public:
		DX11Framebuffer(const FramebufferDescription& desc, DX11GraphicsDevice* device);
		virtual ~DX11Framebuffer() final override;

		FORCEINLINE const Array<ID3D11RenderTargetView*>& get_dx11_rtvs_fast() const;
		FORCEINLINE Array<ID3D11RenderTargetView*> get_dx11_rtvs_slow() const;
		FORCEINLINE ID3D11DepthStencilView* get_dx11_depth_rtv() const;
	private:
		void create(const FramebufferDescription& desc, DX11GraphicsDevice* device);
	private:
		Array<ID3D11RenderTargetView*> RenderTargets;
		ID3D11DepthStencilView* DepthTarget;
	};


}