#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Structures/Array.h>
#include <Engine/Graphics/Resource/ResourceViewDescription.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API ResourceView : public DeviceObject
	{
	public:
		ResourceView(const ResourceViewDescription& description);
		virtual ~ResourceView() = 0 {}

		FORCEINLINE DeviceObject* get_resource() const;
	private:
		DeviceObject* Resource;
	};


}