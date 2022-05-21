#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{

	/// <summary>
	/// Supported GUIRenderer backend flags
	/// </summary>
	enum DOPE_ENGINE_API GUIRendererBackendFlags
	{
		None = 0,
		HasGamepad = 1 << 0,
		HasMouseCursors = 1 << 1,
		HasSetMousePos = 1 << 2,
		RendererHasVertexOffset = 1 << 3,
		PlatformHasViewports = 1 << 10,
		HasMouseHoveredViewport = 1 << 11,
		RendererHasViewports = 1 << 12
	};
}