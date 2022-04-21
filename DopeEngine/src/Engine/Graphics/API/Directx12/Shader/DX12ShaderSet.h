#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Shader/ShaderSet.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12ShaderSet : public ShaderSet
	{
	public:
		DX12ShaderSet(const Array<Shader*>& shaders, DX12GraphicsDevice* device);
		virtual ~DX12ShaderSet() final override;



		// Inherited via ShaderSet
		virtual void create_set() override;

	};


}