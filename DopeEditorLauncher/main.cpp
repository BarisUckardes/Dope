#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Application.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Core/Assert.h>
#include <Engine/Application/Modules/WorldResolverModule.h>
#include <Engine/Application/Modules/TestingModule.h>
#include <Engine/Application/Modules/TestRenderingModule.h>
#include <Engine/Threading/Thread.h>
#include "TestReflectionClass.h"
#include <Engine/Audio/Loader/IAudioLoader.h>
#include <Engine/Audio/Loader/AudioLoadResult.h>
#include <Engine/File/PlatformFile.h>


void* test_thread(void* param)
{
	unsigned int* p = (unsigned int*)param;
	*p = 118;
	return nullptr;
}
int main(int argumentCount, char** arguments)
{
	TestReflectionClass test;
	DopeEngine::ReflectableType* type = TestReflectionClass_reflection_type_accessor_::get_owner_type();
	type = typeof(TestReflectionClass);

	LOG("Reflection", "Type name : %s", *type->get_name());

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
	app.register_pending_module<DopeEngine::WorldResolverModule>();
	app.register_pending_module<DopeEngine::TestingModule>();
	app.register_pending_module<DopeEngine::TestRenderingModule>();

	Thread thread;
	//unsigned int a = 1;

	//thread.give_new_task(DopeEngine::Delegate<void*, void*>(BIND_EVENT(test_thread)) ,&a);
	//thread.wait_for_task_finish();
	//a = 555;
	//thread.give_new_task(DopeEngine::Delegate<void*, void*>(BIND_EVENT(test_thread)), &a);
	//thread.wait_for_task_finish();
	//
	//LOG("Test app", "Value is : %d", a);


	DopeEngine::IAudioLoader* audioLoader = DopeEngine::IAudioLoader::create(DopeEngine::AudioLoaderType::Wav);
	DopeEngine::AudioLoadResult loadResult = {};
	audioLoader->load("E:\\Dope\\Development\\Resources\\Audio\\TestWAVFile.wav",loadResult);

	/*
	* Run app
	*/
	app.run();

	return 0;
}