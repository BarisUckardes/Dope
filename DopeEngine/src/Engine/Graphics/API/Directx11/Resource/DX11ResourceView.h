#pragma once
#include <Engine/Graphics/Resource/ResourceView.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11ResourceView final : public ResourceView
	{
	public:
		DX11ResourceView(const ResourceViewDescription& desc, DX11GraphicsDevice* device);
		virtual ~DX11ResourceView() final override;

		 DXPTR<ID3D11ShaderResourceView> get_dx11_srv() const;
	private:
		void create(const ResourceViewDescription& desc,DX11GraphicsDevice* device);
		void create_as_texture(const GraphicsDeviceObject* deviceObject, DX11GraphicsDevice* device);
		void create_as_constant_Buffer(const GraphicsDeviceObject* deviceObject, DX11GraphicsDevice* device);
	private:
		DXPTR<ID3D11ShaderResourceView> ShaderResourceView;
	};


}