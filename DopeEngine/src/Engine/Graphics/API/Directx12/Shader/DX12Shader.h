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

		// Inherited via Shader
		virtual void compile() override;
	};


}