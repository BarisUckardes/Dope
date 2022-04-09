#include "WindowFileDropEvent.h"

namespace DopeEngine
{
	WindowFileDropEvent::WindowFileDropEvent(const Array<String>& files)
	{
		Drops = files;
	}
	Array<String> WindowFileDropEvent::get_drops() const
	{
		return Drops;
	}
	ApplicationEventType WindowFileDropEvent::get_type() const
	{
		return ApplicationEventType::WindowFileDrop;
	}
	String WindowFileDropEvent::get_as_string() const
	{
		return "Window file drop(s) -> " + String::get_from_integer(Drops.get_cursor());
	}
}