#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Mouse position changed event class representation
	/// </summary>
	class DOPE_ENGINE_API MousePositionChangedEvent final : public ApplicationEvent
	{
	public:
		MousePositionChangedEvent(const unsigned int x,const unsigned int y);
		~MousePositionChangedEvent() = default;


		/// <summary>
		/// Returns the mouse position in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_x() const;

		/// <summary>
		/// Returns the mouse position in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_y() const;
	private:
		unsigned int X;
		unsigned int Y;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	};


}