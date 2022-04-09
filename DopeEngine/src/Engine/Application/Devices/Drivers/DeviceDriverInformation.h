#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Holds the information of a device driver
	/// </summary>
	class  DOPE_ENGINE_API DeviceDriverInformation
	{
	public:
		DeviceDriverInformation(const String& baseName);
		DeviceDriverInformation() = default;
		~DeviceDriverInformation() = default;

		/// <summary>
		/// Returns the base name of the device driver
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_base_name() const;
	private:
		String BaseName;
	};


}