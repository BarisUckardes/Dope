#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Texture/Texture.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12Texture : public Texture
	{
	public:
		DX12Texture(const TextureDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12Texture() final override;
	};


}