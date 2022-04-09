#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
int main(int argumentCount, char** arguments)
{
	/*
	* Create dummy window
	*/
	DopeEngine::Window* window = DopeEngine::Window::create("Dope Editor", 512, 512);
	window->set_window_visibility(true);

	/*
	* Create graphics device
	*/
	DopeEngine::GraphicsDevice* device = DopeEngine::GraphicsDevice::create(DopeEngine::GraphicsAPIType::OpenGL, window);

	while (true)
	{
		window->poll_messages();
		window->swap_buffers();
	}
	return 0;
}