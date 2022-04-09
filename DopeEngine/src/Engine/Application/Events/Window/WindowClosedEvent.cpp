#include "WindowClosedEvent.h"

namespace DopeEngine
{
	ApplicationEventType WindowClosedEvent::get_type() const
	{
		return ApplicationEventType::WindowClosed;
	}
	String WindowClosedEvent::get_as_string() const
	{
		return "Window Closed";
	}
}