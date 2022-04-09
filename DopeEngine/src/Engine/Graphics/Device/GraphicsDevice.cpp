#include "GraphicsDevice.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLGraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/Directx11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/Directx12GraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VulkanGraphicsDevice.h>
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
				return new Directx11GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx12:
				return new Directx12GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Vulkan:
				return new VulkanGraphicsDevice(ownerWindow);
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