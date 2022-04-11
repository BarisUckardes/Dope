#pragma once
#include <Engine/Application/Events/Mouse/MouseButtonEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Mouse button up event class representation
	/// </summary>
	class DOPE_ENGINE_API MouseButtonUpEvent final : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const unsigned int button);
		~MouseButtonUpEvent() = default;

		// Inherited via MouseButtonEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	};

}