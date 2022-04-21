#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12Framebuffer : public Framebuffer
	{
	public:
		DX12Framebuffer(const FramebufferDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12Framebuffer() final override;
	};


}