#include "MouseButtonDownEvent.h"

namespace DopeEngine
{
	MouseButtonDownEvent::MouseButtonDownEvent(const unsigned int button, const bool holding) : MouseButtonEvent(button)
	{
		Holding = holding;
	}
	bool MouseButtonDownEvent::is_holding() const
	{
		return Holding;
	}
	ApplicationEventType MouseButtonDownEvent::get_type() const
	{
		return ApplicationEventType::MouseButtonDown;
	}
	String MouseButtonDownEvent::get_as_string() const
	{
		return "Mouse button down -> " + String::get_from_integer(get_button());
	}
}