#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Mouse scrolled event class representation
	/// </summary>
	class DOPE_ENGINE_API MouseScrolledEvent final : public ApplicationEvent
	{
	public:
		MouseScrolledEvent(const float amount);
		~MouseScrolledEvent() = default;

		FORCEINLINE float get_amount() const;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	private:
		float Amount;
	};

}
