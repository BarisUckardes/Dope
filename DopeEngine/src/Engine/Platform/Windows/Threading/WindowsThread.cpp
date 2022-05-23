#include "WindowsThread.h"
#include <Engine/Core/Assert.h>


namespace DopeEngine
{

	WindowsThread::WindowsThread(const unsigned int stackSize)
	{
		StackSize = stackSize;
		HasTask = false;
		Running = true;

		create_win32_thread();
	}
	WindowsThread::~WindowsThread()
	{
		delete_win32_thread();
	}
	bool WindowsThread::is_active()
	{
		ThreadStateMutex.lock();
		const bool state = Running;
		ThreadStateMutex.unlock();

		return state;
	}

	void WindowsThread::give_new_task(const Delegate<void*, void*>& function, void* parameterPtr, void* returnPtr)
	{
		wait_for_task_finish();

		TaskMutex.lock();
		ParameterPtr = parameterPtr;
		ReturnPtr = returnPtr;
		UserFunction = function;
		HasTask = true;
		TaskMutex.unlock();
	}
	void WindowsThread::wait_for_task_finish()
	{
		while(has_task()) {}
	}
	void WindowsThread::wait_and_terminate()
	{
		wait_for_task_finish();

		ThreadStateMutex.lock();
		Running = false;
		ThreadStateMutex.unlock();

		wait_win32_thread();

		delete_win32_thread();
	}
	void WindowsThread::force_terminate()
	{
		suspend_win32_thread();

		delete_win32_thread();
	}
	void* WindowsThread::get_return_ptr() const
	{
		return ReturnPtr;
	}
	void WindowsThread::create_win32_thread()
	{
		Handle = CreateThread(
			NULL,
			StackSize,
			(LPTHREAD_START_ROUTINE)win32_thread_function,
			this,
			NULL,
			NULL);

		ASSERT(Handle != NULL, "WindowsThread", "Could not create thread, something is wrong!");
	}
	void WindowsThread::delete_win32_thread()
	{
		if(Handle != NULL)
			CloseHandle(Handle);
		Handle = NULL;
	}
	void WindowsThread::wait_win32_thread()
	{
		WaitForSingleObject(Handle, INFINITE);
	}
	void WindowsThread::suspend_win32_thread()
	{

	}
	void WindowsThread::_set_task_state(const bool state)
	{
		TaskMutex.lock();
		HasTask = state;
		TaskMutex.unlock();
	}
	bool WindowsThread::has_task()
	{
		TaskMutex.lock();
		const bool state = HasTask;
		TaskMutex.unlock();
		return state;
	}
	DWORD WINAPI WindowsThread::win32_thread_function(LPVOID lParam)
	{
		WindowsThread* thread = (WindowsThread*)lParam;

		thread->ThreadStateMutex.lock();
		while (thread->Running)
		{
			thread->ThreadStateMutex.unlock();

			if (!thread->has_task())
				continue;

			thread->TaskMutex.lock();
			if (!thread->UserFunction.is_empty())
				thread->ReturnPtr = thread->UserFunction.invoke(thread->ParameterPtr);
			thread->TaskMutex.unlock();

			thread->_set_task_state(false);

			thread->ThreadStateMutex.lock();
		}

		return 0;
	}
}