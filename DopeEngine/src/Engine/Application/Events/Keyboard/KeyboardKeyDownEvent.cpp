#include "KeyboardKeyDownEvent.h"

namespace DopeEngine
{
    KeyboardKeyDownEvent::KeyboardKeyDownEvent(const unsigned int relatedKey, const bool holding) : KeyboardKeyEvent(relatedKey)
    {
        Holding = holding;
    }
    bool KeyboardKeyDownEvent::is_holding() const
    {
        return Holding;
    }
    ApplicationEventType KeyboardKeyDownEvent::get_type() const
    {
        return ApplicationEventType::KeyboardKeyDown;
    }
    String KeyboardKeyDownEvent::get_as_string() const
    {
        return "Keyboard key down -> " + String::get_from_integer(get_key()) + " is" + (Holding == true ? "" : "not") + "holding";
    }
}