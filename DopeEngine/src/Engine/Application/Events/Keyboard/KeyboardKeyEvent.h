#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Base keyboard key event class representation
	/// </summary>
	class DOPE_ENGINE_API KeyboardKeyEvent : public ApplicationEvent
	{
	public:
		KeyboardKeyEvent(const unsigned int relatedKey);
		~KeyboardKeyEvent() = default;

		FORCEINLINE unsigned int get_key() const;
	private:
		unsigned int RelatedKey;
	};


}