#pragma once
#include <Engine/Core/Symbols.h>
#include <Windows.h>
namespace DopeEngine
{
	/// <summary>
	/// Windows implementation of a mutex 
	/// </summary>
	class DOPE_ENGINE_API WindowsMutex final
	{
	public:
		WindowsMutex();
		 ~WindowsMutex();

		/// <summary>
		/// lokcs the mutex
		/// </summary>
		void lock();

		/// <summary>
		/// Unlocks the mutex
		/// </summary>
		void unlock();
	private:
		void create_win32_mutex();
		void delete_win32_mutex();
	private:
		HANDLE Handle;
	};


}