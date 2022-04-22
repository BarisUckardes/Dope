#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Shader/Shader.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12Shader : public Shader
	{
	public:
		DX12Shader(const ShaderDescription& desc, DX12GraphicsDevice* device);
		virtual ~DX12Shader() final override;

		/// <summary>
		/// Returns the dx12 shader blob
		/// </summary>
		/// <returns></returns>
		ID3DBlob* get_dx12_shader_blob() const;

		// Inherited via Shader
		virtual void compile() override;

	private:
		void _create_shader(const ShaderDescription& desc, DX12GraphicsDevice* device);
	private:
		ID3DBlob* ShaderBlob;
	};


}