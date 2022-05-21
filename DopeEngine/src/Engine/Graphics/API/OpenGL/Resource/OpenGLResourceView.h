#pragma once
#include <Engine/Graphics/Resource/GraphicsResource.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLResourceView final : public GraphicsResource
	{
	public:
		OpenGLResourceView(const GraphicsResourceDesc& description);
		virtual ~OpenGLResourceView() final override;

	};
}