#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Base mouse button event representation class
	/// </summary>
	class DOPE_ENGINE_API MouseButtonEvent : public ApplicationEvent
	{
	public:
		/// <summary>
		/// Returns the related button
		/// </summary>
		/// <returns></returns>
		 unsigned int get_button() const;
	protected:
		MouseButtonEvent(const unsigned int relatedButton);
		~MouseButtonEvent() = default;

	private:
		unsigned int RelatedButton;
	};


}