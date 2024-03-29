#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported asset import types
	/// </summary>
	enum class DOPE_ENGINE_API AssetImportType
	{
		Undefined = 0,
		Virtual = 1,
		Raw = 2,
		Packed = 3
	};
}