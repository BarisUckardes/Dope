#pragma once
#include <Engine/Graphics/Resource/ResourceLayout.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLResourceLayout final : public ResourceLayout
	{
	public:
		OpenGLResourceLayout(const ResourceDescription& description);
		virtual ~OpenGLResourceLayout() final override;
	};


}