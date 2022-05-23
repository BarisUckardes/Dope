#pragma once
#include <Engine/Core/Symbols.h>
//#include <winnt.h>
namespace DopeEngine
{

	/// <summary>
	/// Supported GUIRenderer backend flags
	/// </summary>
	enum class DOPE_ENGINE_API GUIRendererBackendFlags : int
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
	//DEFINE_ENUM_FLAG_OPERATORS(GUIRendererBackendFlags);

	FORCEINLINE static GUIRendererBackendFlags operator|(const GUIRendererBackendFlags a, const GUIRendererBackendFlags b)
	{
		return (GUIRendererBackendFlags)((int)a | (int)b);
	}
}