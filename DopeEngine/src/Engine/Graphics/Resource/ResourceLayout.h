#pragma once
#include <Engine/Graphics/Resource/ResourceLayoutDescription.h>
#include <Engine/Graphics/Device/DeviceObject.h>

namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic resource layout abstraction class
	/// </summary>
	class DOPE_ENGINE_API ResourceLayout : public DeviceObject
	{
	public:
		ResourceLayout(const ResourceLayoutDescription& description);
		virtual ~ResourceLayout() = 0 {}

		/// <summary>
		/// Returns the description
		/// </summary>
		FORCEINLINE ResourceLayoutDescription get_description() const;
	private:
		ResourceLayoutDescription Description;
	};


}