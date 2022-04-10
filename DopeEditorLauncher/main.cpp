#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Application.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
#include <Engine/Application/Modules/WorldResolverModule.h>
#include <Engine/Application/Modules/TestingModule.h>
int main(int argumentCount, char** arguments)
{
	/*
	* Create application
	*/
	DopeEngine::Application app({ "Dope Editor Launcher ",512,512,100,100 },DopeEngine::GraphicsAPIType::OpenGL);

	/*
	* Register modules
	*/
	app.register_pending_module<DopeEngine::WorldResolverModule>();
	app.register_pending_module<DopeEngine::TestingModule>();

	/*
	* Run app
	*/
	app.run();

	return 0;
}