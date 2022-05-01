#pragma once
#include <Engine/Graphics/Resource/ResourceDescription.h>
#include <Engine/Graphics/Device/DeviceObject.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic resource layout abstraction class
	/// </summary>
	class DOPE_ENGINE_API ResourceLayout : public DeviceObject
	{
	public:
		ResourceLayout(const ResourceDescription& description);
		virtual ~ResourceLayout() = 0 {}

		/// <summary>
		/// Returns the description
		/// </summary>
		const ResourceDescription& get_description() const;
	private:
		ResourceDescription Description;
	};


}