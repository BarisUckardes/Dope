#pragma once
#include <Engine/Graphics/Resource/ResourceLayout.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX11ResourceLayout final : public ResourceLayout
	{
	public:
		DX11ResourceLayout(const ResourceDescription& desc,DX11GraphicsDevice* device);
		virtual ~DX11ResourceLayout() final override;

	private:
		void create(const ResourceDescription& desc, DX11GraphicsDevice* device);
	private:
		
	};


}