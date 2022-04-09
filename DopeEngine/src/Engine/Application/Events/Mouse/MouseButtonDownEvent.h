#pragma once
#include <Engine/Application/Events/Mouse/MouseButtonEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Mouse button down event representation class
	/// </summary>
	class DOPE_ENGINE_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const unsigned int button, const bool holding);
		~MouseButtonDownEvent() = default;


		/// <summary>
		/// Returns whether the button is a hold event
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_holding() const;

		// Inherited via MouseButtonEvent
		virtual ApplicationEventType get_type() const override;
		virtual String get_as_string() const override;
	private:
		bool Holding;

		
	};
}



