#include "TextureLoader.h"
#include <STBI/stb_image.h>
namespace DopeEngine
{
	TextureLoadResult TextureLoader::load_texture_from_path(const String& path)
	{
		/*
		* Load stbi 
		*/
		String failReason = "No failure";
		int width = 0;
		int height = 0;
		int depth = 0;
		int channels = 0;
		const Byte* data = stbi_load(*path, &width, &height, &channels, 4);

		/*
		* Validate failure
		*/
		if (data == nullptr) // failed
		{
			/*
			* Get failure message from stbi
			*/
			failReason = stbi_failure_reason();
		}

		/*
		* Create load result
		*/
		TextureLoadResult result{data,failReason,(unsigned int)channels,(unsigned int)width,(unsigned int)height,(unsigned int)depth};
		

		return result;
	}
}