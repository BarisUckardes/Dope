#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Application/Events/ApplicationEventType.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Base application event class
	/// </summary>
	class DOPE_ENGINE_API ApplicationEvent
	{
	public:
		/// <summary>
		/// Returns whether this event is handled or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_handled() const;

		/// <summary>
		/// Returns the event type for this event
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual ApplicationEventType get_type() const = 0;

		/// <summary>
		/// Returns the event message string
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual String get_as_string() const = 0;

		/// <summary>
		/// Marks this event handled
		/// </summary>
		void mark_handled();
	protected:
		ApplicationEvent() : Handled(false) {}
		~ApplicationEvent() = default;
	private:
		bool Handled;
	};
}