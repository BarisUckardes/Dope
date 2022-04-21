#pragma once
#include <Engine/Core/Symbols.h>
#include <Windows.h>
#include <Engine/Event/Delegate.h>
#include <Engine/Threading/Mutex.h>
namespace DopeEngine
{

	/// <summary>
	/// Windows implementation of a thread
	/// </summary>
	class DOPE_ENGINE_API WindowsThread final
	{
		friend DWORD WINAPI win32_thread_function(LPVOID lParam);
	public:
		WindowsThread(const unsigned int stackSize = 0);
		~WindowsThread();

		/// <summary>
		/// Returns whether this thread is active or not
		/// </summary>
		/// <returns></returns>
		 bool is_active();

		/// <summary>
		/// Returns whether this thread has a task ongoing or not
		/// </summary>
		/// <returns></returns>
		 bool has_task();

		/// <summary>
		/// Starts the thread
		/// </summary>
		void give_new_task(const Delegate<void*, void*>& function,void* parameterPtr = nullptr, void* returnPtr = nullptr);

		/// <summary>
		/// Waits this thread until it finishes
		/// </summary>
		void wait_for_task_finish();

		/// <summary>
		/// Waits for the current task to finish and then terminates
		/// </summary>
		void wait_and_terminate();

		/// <summary>
		/// Terminates immediately
		/// </summary>
		void force_terminate();

		/// <summary>
		/// Returns the return object ptr
		/// </summary>
		/// <returns></returns>
		void* get_return_ptr() const;
	private:
		static DWORD WINAPI win32_thread_function(LPVOID lParam);
		void create_win32_thread();
		void delete_win32_thread();
		void wait_win32_thread();
		void suspend_win32_thread();
		void _set_task_state(const bool state);
	private:
		Delegate<void*, void*> UserFunction;
		Mutex TaskMutex;
		Mutex ThreadStateMutex;
		HANDLE Handle;
		void* ParameterPtr;
		void* ReturnPtr;
		unsigned int StackSize;
		bool Running;
		bool HasTask;
	};


}