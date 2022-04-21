#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Resource/ResourceView.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ResourceView : public ResourceView
	{
	public:
		DX12ResourceView(const ResourceViewDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12ResourceView() final override;

	};
}