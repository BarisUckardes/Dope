#pragma once
#include <Engine/Application/Events/Keyboard/KeyboardKeyEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Keyboard char event representation class
	/// </summary>
	class DOPE_ENGINE_API KeyboardCharEvent final : public KeyboardKeyEvent
	{
	public:
		KeyboardCharEvent(const unsigned int relatedKey);
		~KeyboardCharEvent() = default;

		// Inherited via KeyboardKeyEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	};


}