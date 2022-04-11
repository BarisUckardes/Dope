#pragma once
#include <Engine/Event/Delegate.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	/// <summary>
	/// Simple event class
	/// </summary>
	/// <typeparam name="TReturn"></typeparam>
	/// <typeparam name="...TParameters"></typeparam>
	template<typename TReturn,typename...TParameters>
	class DOPE_ENGINE_API Event final
	{
	public:
		Event() = default;
		~Event() = default;

		/// <summary>
		/// Returns the subscription invocation list
		/// </summary>
		/// <returns></returns>
		Array<Delegate<TReturn(TParameters...)>> get_invocation_list() const;

		/// <summary>
		/// Invokes this event's subscription invocation list
		/// </summary>
		/// <param name="...parameters"></param>
		void invoke(TParameters... parameters);

		
		void operator +=(const Delegate<TReturn(TParameters...)>& delegate);
		void operator -=(const Delegate<TReturn(TParameters...)>& delegate);
	private:
		Array<Delegate<TReturn,TParameters...>> Subscriptions;
	};


	

	template<typename TReturn, typename ...TParameters>
	FORCEINLINE Array<Delegate<TReturn(TParameters...)>> Event<TReturn, TParameters...>::get_invocation_list() const
	{
		return Subscriptions;
	}

	template<typename TReturn, typename ...TParameters>
	FORCEINLINE void Event<TReturn, TParameters...>::invoke(TParameters ...parameters)
	{
		for (unsigned int i = 0; i < Subscriptions.get_cursor(); i++)
		{
			Subscriptions[i](parameters);
		}
	}

	template<typename TReturn, typename ...TParameters>
	FORCEINLINE void Event<TReturn, TParameters...>::operator+=(const Delegate<TReturn(TParameters...)>& delegate)
	{
		Subscriptions.add(delegate);
	}
	template<typename TReturn, typename ...TParameters>
	FORCEINLINE void Event<TReturn, TParameters...>::operator-=(const Delegate<TReturn(TParameters...)>& delegate)
	{
		Subscriptions.remove(delegate);
	}
}