#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	enum class DOPE_ENGINE_API ApplicationEventType
	{
		/// <summary>
		/// The event type is undefined
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The event type is a keyboard key down
		/// </summary>
		KeyboardKeyDown = 1,

		/// <summary>
		/// The event type is a keyboard key up
		/// </summary>
		KeyboardKeyUp = 2,

		/// <summary>
		/// The event type is a keyboard text char input
		/// </summary>
		KeyboardChar = 4,

		/// <summary>
		/// Represents the window resize event
		/// </summary>
		WindowResized = 5,

		/// <summary>
		/// Represents the window close event
		/// </summary>
		WindowClosed = 6,

		/// <summary>
		/// Represents the window position change event
		/// </summary>
		WindowPositionChanged = 7,

		/// <summary>
		/// Represents a mouse button down event
		/// </summary>
		MouseButtonDown = 8,

		/// <summary>
		/// Represents a mouse button up event
		/// </summary>
		MouseButtonUp = 9,

		/// <summary>
		/// Represents a mouse scrolled event
		/// </summary>
		MouseScrolled = 10,

		/// <summary>
		/// Represetns a mouse position changed event
		/// </summary>
		MousePositionChanged = 11,

		/// <summary>
		/// Represents a file drop to window
		/// </summary>
		WindowFileDrop = 12
	};
}