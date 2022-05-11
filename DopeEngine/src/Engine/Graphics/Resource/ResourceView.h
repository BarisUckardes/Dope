#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Structures/Array.h>
#include <Engine/Graphics/Resource/ResourceViewDescription.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API ResourceView : public GraphicsDeviceObject
	{
	public:
		ResourceView(const ResourceViewDescription& description);
		virtual ~ResourceView() = 0 {}

		GraphicsDeviceObject* get_resource() const;
	private:
		GraphicsDeviceObject* Resource;
	};


}