#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Window position changed event representation class
	/// </summary>
	class DOPE_ENGINE_API WindowPositionChangedEvent final : public ApplicationEvent
	{
	public:
		WindowPositionChangedEvent(const unsigned int x, const unsigned int y);
		~WindowPositionChangedEvent() = default;

		FORCEINLINE unsigned int get_x() const;
		FORCEINLINE unsigned int get_y() const;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	private:
		unsigned int X;
		unsigned int Y;
	};


}