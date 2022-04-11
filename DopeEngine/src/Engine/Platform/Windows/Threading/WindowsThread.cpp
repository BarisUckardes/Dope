#include "WindowsThread.h"
#include <Engine/Core/Assert.h>


namespace DopeEngine
{

	WindowsThread::WindowsThread(const unsigned int stackSize)
	{
		/*
		* Initialize
		*/
		StackSize = stackSize;
		HasTask = false;
		Running = true;

		/*
		* Create win32 thread
		*/
		create_win32_thread();
	}
	WindowsThread::~WindowsThread()
	{
		/*
		* Delete win32 thread
		*/
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
		/*
		* Wait for the current task to finish
		*/
		wait_for_task_finish();

		/*
		* Set new task
		*/
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
		/*
		* Wait task
		*/
		wait_for_task_finish();

		/*
		* Terminate
		*/
		ThreadStateMutex.lock();
		Running = false;
		ThreadStateMutex.unlock();

		/*
		* Wait for win32 thread to reach termination
		*/
		wait_win32_thread();

		/*
		* Delete win32 thread
		*/
		delete_win32_thread();
	}
	void WindowsThread::force_terminate()
	{
		/*
		* Suspend thread immediately
		*/
		suspend_win32_thread();

		/*
		* Terminate
		*/
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
		/*
		* Wait for the thread
		*/
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
		/*
		* Get thread
		*/
		WindowsThread* thread = (WindowsThread*)lParam;

		/*
		* Thread task loop
		*/
		thread->ThreadStateMutex.lock();
		while (thread->Running)
		{
			/*
			* Unlock access to thread state
			*/
			thread->ThreadStateMutex.unlock();

			/*
			* Validate if has a task
			*/
			if (!thread->has_task())
				continue;

			/*
			* Run user function
			*/
			thread->TaskMutex.lock();
			if (!thread->UserFunction.is_empty())
			{
				/*
				* Lock user thread function
				*/
				thread->ReturnPtr = thread->UserFunction.invoke(thread->ParameterPtr);
			}
			thread->TaskMutex.unlock();

			/*
			* Set task is complete
			*/
			thread->_set_task_state(false);

			/*
			* Lock access to thread state
			*/
			thread->ThreadStateMutex.lock();
		}

		LOG("WindowsThread", "Thread finalized!");
		return 0;
	}
}