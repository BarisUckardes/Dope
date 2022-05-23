#pragma once
#include <Engine/Application/Events/Keyboard/KeyboardKeyEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Keyboard key down event class representation
	/// </summary>
	class DOPE_ENGINE_API KeyboardKeyDownEvent final : public KeyboardKeyEvent
	{
	public:
		KeyboardKeyDownEvent(const unsigned int relatedKey, const bool holding);
		~KeyboardKeyDownEvent() = default;

		FORCEINLINE bool is_holding() const;

		// Inherited via KeyboardKeyEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;
	private:
		bool Holding;
	};


}