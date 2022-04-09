#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Application.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
int main(int argumentCount, char** arguments)
{
	/*
	* Create application
	*/
	DopeEngine::Application app({ "Dope Editor Launcher ",512,512,100,100 },DopeEngine::GraphicsAPIType::OpenGL);

	/*
	* Get window
	*/
	DopeEngine::Window* window = app.get_app_window();

	/*
	* Set window visible
	*/
	window->set_window_visibility(true);

	/*
	* Dummy application loop
	*/
	while (true)
	{
		window->poll_messages();
		window->swap_buffers();
	}
	return 0;
}