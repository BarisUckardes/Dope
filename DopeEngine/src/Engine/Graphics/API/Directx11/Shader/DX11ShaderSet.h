#pragma once
#include <Engine/Graphics/Shader/ShaderSet.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX11ShaderSet : public ShaderSet
	{
	public:
		DX11ShaderSet(const Array<Shader*>& shaders);
		virtual ~DX11ShaderSet() final override;

		// Inherited via ShaderSet
		virtual void create_set() override;
	};


}