#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Application.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
int main(int argumentCount, char** arguments)
{
	/*
	* Create application
	*/
	DopeEngine::Application app({ "Dope Editor Launcher ",512,512,100,100 },DopeEngine::GraphicsAPIType::Directx11);
	DopeEngine::Window* window = app.get_app_window();
	window->set_window_visibility(true);
	while (true)
	{
		window->poll_messages();
		window->swap_buffers();
	}
	return 0;
}