#pragma once
#include <Engine/Core/Symbols.h>


namespace DopeEngine
{
	enum DOPE_ENGINE_API GUIRendererConfigFlags
	{
		GUIRendererConfigFlags_None = 0,
		GUIRendererConfigFlags_NavigationKeyboardEnabled = 1 << 0,
		GUIRendererConfigFlags_NavigationGamepadEnabled = 1 << 1,
		GUIRendererConfigFlags_NavigationMousePositionEnabled = 1 << 2,
		GUIRendererConfigFlags_NavigationDontCaptureKeyboard = 1 << 3,
		GUIRendererConfigFlags_MouseDisabled = 1 << 4,
		GUIRendererConfigFlags_MouseCursorChangeDisabled = 1 << 5,
		GUIRendererConfigFlags_DockingEnabled = 1 << 6,
		GUIRendererConfigFlags_ViewportsEnabled = 1 << 10,
		GUIRendererConfigFlags_ViewportDpiScalingEnabled = 1 << 14,
		GUIRendererConfigFlags_FontDpiScalingEnabled = 1 << 15,
		GUIRendererConfigFlags_SupportsSRGB = 1 << 20,
		GUIRendererConfigFlags_SupportsTouchScreen = 1 << 21
	};
}