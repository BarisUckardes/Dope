#pragma once
#include <Engine/Core/Symbols.h>
#include <functional>

namespace DopeEngine
{
	/// <summary>
	/// Basic delegate class
	/// </summary>
	/// <typeparam name="TReturn"></typeparam>
	/// <typeparam name="...TParameters"></typeparam>
	template<typename TReturn,typename... TParameters>
	class DOPE_ENGINE_API Delegate
	{
	public:
		Delegate(const std::function<TReturn(TParameters...)>& function)
		{

		}
		~Delegate() = default;


		/// <summary>
		/// Returns the address of the target function pointer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE size_t GetAddress() const
		{
			typedef TReturn(fnType)(TParameters...);
			fnType** fnPointer = GetFunctionPtr().template target<fnType*>();
			return (size_t)*fnPointer;
		}

		/// <summary>
		/// invokes the target function ptr with the given parameter set
		/// </summary>
		/// <param name="...parameters"></param>
		void invoke(TParameters... parameters)
		{
			FunctionPtr(parameters...);
		}

	private:
		/// <summary>
		/// Returns the function pointer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE std::function<TReturn(TParameters...)> GetFunctionPtr() const
		{
			return FunctionPtr;
		}

	private:
		std::function<TReturn(TParameters...)> FunctionPtr;
	};

	template<typename TReturn, typename...TParameters>
	static bool operator ==(const Delegate<TReturn, TParameters...>& a, const Delegate<TReturn, TParameters...>& b)
	{
		return a.GetAddress() == b.GetAddress();
	}
	template<typename TReturn, typename...TParameters>
	static bool operator !=(const Delegate<TReturn, TParameters...>& a, const Delegate<TReturn, TParameters...>& b)
	{
		return a.GetAddress() != b.GetAddress();
	}
}