#pragma once
#include <Engine/Graphics/Resource/ResourceView.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLResourceView final : public ResourceView
	{
	public:
		OpenGLResourceView(const ResourceViewDescription& description);
		virtual ~OpenGLResourceView() final override;

	};
}