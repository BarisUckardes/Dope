#pragma once
#include <Engine/Application/Events/Keyboard/KeyboardKeyEvent.h>

namespace DopeEngine
{
	/// <summary>
	/// Keyboard key down event class representation
	/// </summary>
	class DOPE_ENGINE_API KeyboardKeyDownEvent : public KeyboardKeyEvent
	{
	public:
		KeyboardKeyDownEvent(const unsigned int relatedKey, const bool holding);
		~KeyboardKeyDownEvent() = default;

		/// <summary>
		/// Returns whether this keyboard key is holding at the moment
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_holding() const;

		// Inherited via KeyboardKeyEvent
		virtual ApplicationEventType get_type() const override;
		virtual String get_as_string() const override;
	private:
		bool Holding;
	};


}