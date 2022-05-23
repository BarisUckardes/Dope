#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Holds the information of a device driver
	/// </summary>
	class DOPE_ENGINE_API DeviceDriverInformation final
	{
	public:
		DeviceDriverInformation(const String& baseName);
		DeviceDriverInformation() = default;
		~DeviceDriverInformation() = default;

		String get_base_name() const;
	private:
		String BaseName;
	};


}