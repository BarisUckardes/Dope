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

		FORCEINLINE const Array<DeviceObject*>& get_resources_fast() const;
		FORCEINLINE Array<DeviceObject*> get_resources_slow() const;
		FORCEINLINE unsigned int get_resource_count() const;
	private:
		Array<DeviceObject*> Resources;
		unsigned int ResourceCount;
	};


}