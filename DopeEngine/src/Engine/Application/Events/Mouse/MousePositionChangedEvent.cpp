#include "MousePositionChangedEvent.h"

namespace DopeEngine
{
    MousePositionChangedEvent::MousePositionChangedEvent(const unsigned int x, const unsigned int y)
    {
        X = x;
        Y = y;
    }
    unsigned int MousePositionChangedEvent::get_x() const
    {
        return X;
    }
    unsigned int MousePositionChangedEvent::get_y() const
    {
        return Y;
    }
    ApplicationEventType MousePositionChangedEvent::get_type() const
    {
        return ApplicationEventType::MousePositionChanged;
    }
    String MousePositionChangedEvent::get_as_string() const
    {
        return "Mouse position changed to X:" + String::get_from_integer(X) + " Y:" + String::get_from_integer(Y);
    }
}