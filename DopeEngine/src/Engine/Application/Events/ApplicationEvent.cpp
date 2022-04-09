#include "ApplicationEvent.h"

namespace DopeEngine
{
	bool ApplicationEvent::is_handled() const
	{
		return Handled;
	}
	void ApplicationEvent::mark_handled()
	{
		Handled = true;
	}
}