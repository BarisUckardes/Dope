#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Application.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
#include <Engine/Application/Modules/WorldFunctionExecutorModule.h>
#include <Engine/Application/Modules/TestingModule.h>
#include <Engine/Application/Modules/TestRenderingModule.h>
#include <Engine/Threading/Thread.h>
#include <Engine/Audio/Loader/IAudioLoader.h>
#include <Engine/Audio/Loader/AudioLoadResult.h>
#include <Engine/File/PlatformFile.h>
#include <Editor/Module/EditorModule.h>
void* test_thread(void* param)
{
	unsigned int* p = (unsigned int*)param;
	*p = 118;
	return nullptr;
}
int main(int argumentCount, char** arguments)
{
	/*
	* Create application
	*/
	DopeEngine::Application app(
		{ "Dope Editor Launcher ",512,512,100,100 },
		DopeEngine::GraphicsAPIType::Directx11,
		DopeEngine::AudioAPIType::OpenAL);

	/*
	* Register modules
	*/
	app.register_pending_module<DopeEngine::WorldFunctionExecutorModule>();
	app.register_pending_module<DopeEngine::TestingModule>();
	app.register_pending_module<DopeEngine::TestRenderingModule>();
	//app.register_pending_module<DopeEditor::EditorModule>();

	Thread thread;
	//unsigned int a = 1;

	//thread.give_new_task(DopeEngine::Delegate<void*, void*>(BIND_EVENT(test_thread)) ,&a);
	//thread.wait_for_task_finish();
	//a = 555;
	//thread.give_new_task(DopeEngine::Delegate<void*, void*>(BIND_EVENT(test_thread)), &a);
	//thread.wait_for_task_finish();
	//
	//LOG("Test app", "Value is : %d", a);

	/*
	* Run app
	*/
	app.run();

	return 0;
}