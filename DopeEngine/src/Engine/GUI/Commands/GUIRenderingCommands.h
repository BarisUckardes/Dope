#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/GUI/Flags/GUIWindowFlags.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents the gui rendering commands of an GUIRenderer instance
	/// </summary>
	class DOPE_ENGINE_API GUIRenderingCommands
	{
		friend class GUIRenderer;
	public:
		/// <summary>
		/// Creates and starts the rendering of anew window
		/// </summary>
		/// <param name="title"></param>
		/// <param name="isOpen"></param>
		/// <param name="flags"></param>
		/// <returns></returns>
		FORCEINLINE bool create_window(const String& title,bool* isOpen,const GUIWindowFlags flags = GUIWindowFlags::None) const;

		/// <summary>
		/// Finalizes the rendering of the last window
		/// </summary>
		FORCEINLINE void finalize_window() const;

		/// <summary>
		/// Demo window
		/// </summary>
		FORCEINLINE void create_demo_window() const;
	private:
		GUIRenderingCommands() = default;
		~GUIRenderingCommands() = default;
	};


}