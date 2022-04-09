#include "KeyboardCharEvent.h"

namespace DopeEngine
{
    KeyboardCharEvent::KeyboardCharEvent(const unsigned int relatedKey) : KeyboardKeyEvent(relatedKey)
    {

    }
    ApplicationEventType KeyboardCharEvent::get_type() const
    {
        return ApplicationEventType::KeyboardChar;
    }
    String KeyboardCharEvent::get_as_string() const
    {
        return "Keyboard char : " + String::get_from_integer(get_key());
    }
}