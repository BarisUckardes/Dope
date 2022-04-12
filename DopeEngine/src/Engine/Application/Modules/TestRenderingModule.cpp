#include "TestRenderingModule.h"
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{

	void TestRenderingModule::initialize()
	{

	}
	void TestRenderingModule::update()
	{
		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();
		CommandBuffer* buffer = device->create_command_buffer();
		buffer->lock();
		buffer->clear_color({ 1u,0u,0u,1u });
		buffer->unlock();
		device->delete_device_object(buffer);
	}
	void TestRenderingModule::finalize()
	{

	}
	void TestRenderingModule::on_receive_application_event(ApplicationEvent* event)
	{

	}
}