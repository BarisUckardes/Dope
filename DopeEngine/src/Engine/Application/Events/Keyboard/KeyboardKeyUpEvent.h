#pragma once
#include <Engine/Application/Events/Keyboard/KeyboardKeyEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Keyboard key up event class representation
	/// </summary>
	class DOPE_ENGINE_API KeyboardKeyUpEvent : public KeyboardKeyEvent
	{
	public:
		KeyboardKeyUpEvent(const unsigned int relatedKey);
		~KeyboardKeyUpEvent() = default;

		// Inherited via KeyboardKeyEvent
		virtual ApplicationEventType get_type() const override;
		virtual String get_as_string() const override;
	};


}