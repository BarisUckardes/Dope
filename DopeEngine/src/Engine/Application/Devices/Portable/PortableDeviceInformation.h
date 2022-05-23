#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Hold's the descriptive device information
	/// </summary>
	class DOPE_ENGINE_API PortableDeviceInformation final

	{
	public:
		PortableDeviceInformation(const String& manufacturer,const String& friendlyName,const String& description);
		PortableDeviceInformation() = default;
		~PortableDeviceInformation() = default;

		FORCEINLINE String get_manufacturer() const;
		FORCEINLINE String get_friendly_name() const;
		FORCEINLINE String get_description() const;
	private:
		String Manufacturer;
		String FriendlyName;
		String Description;
	};


}