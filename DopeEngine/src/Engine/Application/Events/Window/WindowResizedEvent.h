#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Window resize event representation class
	/// </summary>
	class DOPE_ENGINE_API WindowResizedEvent : public ApplicationEvent
	{
	public:
		WindowResizedEvent(const unsigned int width, const unsigned int height);
		~WindowResizedEvent() = default;

		/// <summary>
		/// Returns the new width of the window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the new height of the window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_height() const;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override;
		virtual String get_as_string() const override;
	private:
		unsigned int Width;
		unsigned int Height;

		
	};


}