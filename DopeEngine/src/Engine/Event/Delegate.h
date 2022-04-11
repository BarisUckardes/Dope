#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/EventWorks.h>

namespace DopeEngine
{
	/// <summary>
	/// Basic delegate class
	/// </summary>
	/// <typeparam name="TReturn"></typeparam>
	/// <typeparam name="...TParameters"></typeparam>
	template<typename TReturn,typename... TParameters>
	class Delegate final
	{
	public:
		Delegate(const std::function<TReturn(TParameters...)>& function) : FunctionPtr(function),Empty(false) {}
		Delegate() : Empty(true) {}
		~Delegate() = default;


		FORCEINLINE bool is_empty() const { return Empty; }
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
		TReturn invoke(TParameters... parameters)
		{
			return FunctionPtr(parameters...);
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
		bool Empty;
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