#include "MouseScrolledEvent.h"


namespace DopeEngine
{
	MouseScrolledEvent::MouseScrolledEvent(const float amount)
	{
		Amount = amount;
	}
	float MouseScrolledEvent::get_amount() const
	{
		return Amount;
	}
	ApplicationEventType MouseScrolledEvent::get_type() const
	{
		return ApplicationEventType::MouseScrolled;
	}
	String MouseScrolledEvent::get_as_string() const
	{
		return "Mouse scrolled -> " + String::get_from_float(Amount);
	}
}