#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Structures/Array.h>
#include <Engine/Graphics/Resource/GraphicsResourceDesc.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API GraphicsResource : public GraphicsDeviceObject
	{
	public:
		GraphicsResource(const GraphicsResourceDesc& description);
		virtual ~GraphicsResource() = 0 {}

		GraphicsDeviceObject* get_resource() const;
	private:
		GraphicsDeviceObject* Resource;
	};


}