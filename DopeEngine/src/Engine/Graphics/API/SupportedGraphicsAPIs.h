#pragma once
#include <Engine/Graphics/API/GraphicsAPIType.h>
#include <Engine/Structures/Array.h>

namespace DopeEngine
{

#ifdef DOPE_OS_WINDOWS
	const static GraphicsAPIType SupportedAPITypes[] =
	{
		GraphicsAPIType::Directx11,
		GraphicsAPIType::Directx12,
		GraphicsAPIType::OpenGL,
		GraphicsAPIType::Vulkan
	};
	const static unsigned char SupportedAPICount = 4;
#elif DOPE_OS_LINUX
	const static GraphicsAPIType SupportedAPITypes[] =
	{
		GraphicsAPIType::OpenGL,
		GraphicsAPIType::Vulkan
	};
	const static unsigned char SupportedAPICount = 2;
#endif

}
