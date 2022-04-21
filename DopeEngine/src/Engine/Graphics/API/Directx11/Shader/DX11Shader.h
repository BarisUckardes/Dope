#pragma once
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11Shader final : public Shader
	{
	public:
		DX11Shader(const ShaderDescription& description, DX11GraphicsDevice* device);
		virtual ~DX11Shader() final override;

		 DXPTR<ID3D11VertexShader> get_dx11_vertex_shader() const;
		 DXPTR<ID3D11PixelShader> get_dx11_fragment_shader() const;
		 DXPTR<ID3DBlob> get_dx11_blob() const;
		// Inherited via Shader
		virtual void compile() override;
	private:
		DX11GraphicsDevice* Device;
		DXPTR<ID3D11VertexShader> VertexShader;
		DXPTR<ID3D11PixelShader> FragmentShader;
		DXPTR<ID3DBlob> ShaderBlob;
	};
}