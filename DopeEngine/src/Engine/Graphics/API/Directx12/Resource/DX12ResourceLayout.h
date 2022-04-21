#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Resource/ResourceLayout.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ResourceLayout : public ResourceLayout
	{
	public:
		DX12ResourceLayout(const ResourceDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12ResourceLayout() final override;

	private:
	};


}