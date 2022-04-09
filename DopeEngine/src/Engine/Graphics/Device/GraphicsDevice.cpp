#include "GraphicsDevice.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLGraphicsDevice.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDevice* GraphicsDevice::create(GraphicsAPIType api, Window* ownerWindow)
	{
		switch (api)
		{
			case DopeEngine::GraphicsAPIType::Undefined:
				ASSERT(false,"GraphicsDevice", "Specified graphics api type is undefined!");
				break;
			case DopeEngine::GraphicsAPIType::OpenGL:
				return new OpenGLGraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx11:
				break;
			case DopeEngine::GraphicsAPIType::Directx12:
				break;
			case DopeEngine::GraphicsAPIType::Vulkna:
				break;
			default:
				break;
		}
		ASSERT(false,"GraphicsDevice", "Specified graphics api type is not valid!");
		return nullptr;
	}

	GraphicsDevice::GraphicsDevice(Window* ownerWindow)
	{
		OwnerWindow = ownerWindow;
	}
	
	

	bool GraphicsDevice::is_current() const
	{
		return Current;
	}

	const Window* GraphicsDevice::get_owner_window() const
	{
		return OwnerWindow;
	}
	void GraphicsDevice::make_current()
	{
		/*
		* Calll api implementation
		*/
		make_current_impl();

		/*
		* Set current state
		*/
		Current = true;
	}
}