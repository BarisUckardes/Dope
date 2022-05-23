#pragma once
#include <Engine/Core/Symbols.h>


namespace DopeEngine
{
	/// <summary>
	/// Supported GUIRenderer configuration flags
	/// </summary>
	enum class DOPE_ENGINE_API GUIRendererConfigFlags : int
	{
		None = 0,
		NavigationKeyboardEnabled = 1 << 0,
		NavigationGamepadEnabled = 1 << 1,
		NavigationMousePositionEnabled = 1 << 2,
		NavigationDontCaptureKeyboard = 1 << 3,
		MouseDisabled = 1 << 4,
		MouseCursorChangeDisabled = 1 << 5,
		DockingEnabled = 1 << 6,
		ViewportsEnabled = 1 << 10,
		ViewportDpiScalingEnabled = 1 << 14,
		FontDpiScalingEnabled = 1 << 15,
		SupportsSRGB = 1 << 20,
		SupportsTouchScreen = 1 << 21
	};

	FORCEINLINE static GUIRendererConfigFlags operator |(const GUIRendererConfigFlags a, const GUIRendererConfigFlags b)
	{
		return (GUIRendererConfigFlags)((int)a | (int)b);
	}
}