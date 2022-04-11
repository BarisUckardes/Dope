#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Window closed event representation class
	/// </summary>
	class DOPE_ENGINE_API WindowClosedEvent final : public ApplicationEvent
	{
	public:
		WindowClosedEvent() = default;
		~WindowClosedEvent() = default;


		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	};


}