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
		bool is_handled() const;
		void mark_handled();

		virtual ApplicationEventType get_type() const = 0;
		virtual String get_as_string() const = 0;
		
		~ApplicationEvent() = default;
	protected:
		ApplicationEvent() : Handled(false) {}
	private:
		bool Handled;
	};
}