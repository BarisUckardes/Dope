#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Math/Vector3f.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API GUIRenderingCommands
	{
		friend class GUIRenderer;
	public:
		FORCEINLINE void create_window(const String& title,bool* isCollapsed,bool* isOpen) const;
		FORCEINLINE void finalize_window() const;
		FORCEINLINE void create_demo_window() const;
	private:
		GUIRenderingCommands() = default;
		~GUIRenderingCommands() = default;
	};


}