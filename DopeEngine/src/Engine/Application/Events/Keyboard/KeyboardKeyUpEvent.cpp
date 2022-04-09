#include "KeyboardKeyUpEvent.h"

namespace DopeEngine
{
	KeyboardKeyUpEvent::KeyboardKeyUpEvent(const unsigned int relatedKey) : KeyboardKeyEvent(relatedKey)
	{

	}
	ApplicationEventType KeyboardKeyUpEvent::get_type() const
	{
		return ApplicationEventType::KeyboardKeyUp;
	}
	String KeyboardKeyUpEvent::get_as_string() const
	{
		return "Keyboard key up -> " + String::get_from_integer(get_key());
	}
}