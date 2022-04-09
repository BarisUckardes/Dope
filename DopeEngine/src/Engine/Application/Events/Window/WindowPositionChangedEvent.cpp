#include "WindowPositionChangedevent.h"

namespace DopeEngine
{
    WindowPositionChangedEvent::WindowPositionChangedEvent(const unsigned int x, const unsigned int y)
    {
        X = x;
        Y = y;
    }
    unsigned int WindowPositionChangedEvent::get_x() const
    {
        return X;
    }
    unsigned int WindowPositionChangedEvent::get_y() const
    {
        return Y;
    }
    ApplicationEventType WindowPositionChangedEvent::get_type() const
    {
        return ApplicationEventType::WindowPositionChanged;
    }
    String WindowPositionChangedEvent::get_as_string() const
    {
        return "Window positon changed to X:" + String::get_from_integer(X) + " Y:" + String::get_from_integer(Y);
    }
}