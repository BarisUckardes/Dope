#include "MouseButtonUpEvent.h"

namespace DopeEngine
{
	MouseButtonUpEvent::MouseButtonUpEvent(const unsigned int button) : MouseButtonEvent(button)
	{

	}
	ApplicationEventType MouseButtonUpEvent::get_type() const
	{
		return ApplicationEventType::MouseButtonUp;
	}
	String MouseButtonUpEvent::get_as_string() const
	{
		return "Mouse button up -> " + String::get_from_integer(get_button());
	}
}