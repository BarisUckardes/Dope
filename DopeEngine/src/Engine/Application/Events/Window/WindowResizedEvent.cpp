#include "WindowResizedEvent.h"

namespace DopeEngine
{
    WindowResizedEvent::WindowResizedEvent(const unsigned int width, const unsigned int height)
    {
        Width = width;
        Height = height;
    }
    unsigned int WindowResizedEvent::get_width() const
    {
        return Width;
    }
    unsigned int WindowResizedEvent::get_height() const
    {
        return Height;
    }
    ApplicationEventType WindowResizedEvent::get_type() const
    {
        return ApplicationEventType::WindowResized;
    }
    String WindowResizedEvent::get_as_string() const
    {
        return "Window resized to X:" + String::get_from_integer(Width) + " Y:" + String::get_from_integer(Height);
    }
}