#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Utils/TextureLoader/TextureLoadResult.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API TextureLoader
	{
	public:
		TextureLoader() = delete;
		~TextureLoader() = delete;

		static TextureLoadResult load_texture_from_path(const String& path);
	};


}