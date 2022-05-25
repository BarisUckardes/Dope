#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Graphics/API/GraphicsAPIType.h>

namespace DopeEngine
{
	class GraphicsDevice;
	class GUIRenderer;
	class ApplicationEvent;
	class GraphicsCommandBuffer;
	class GUIEventCommands;
	class GUIRenderingCommands;
	class GUILayoutCommands;
}

namespace DopeEditor
{
	/// <summary>
	/// GUI component specialized in Editor gui operations
	/// </summary>
	class DOPE_EDITOR_API EditorGUIPainter
	{
	public:
		EditorGUIPainter(DopeEngine::GraphicsDevice* device);
		~EditorGUIPainter();

		FORCEINLINE DopeEngine::GUIRenderingCommands* get_rendering_commands() const;
		FORCEINLINE DopeEngine::GUIEventCommands* get_event_commands() const;
		FORCEINLINE DopeEngine::GUILayoutCommands* get_layout_commands() const;

		void StartPainting();
		void FinalizePainting(const DopeEngine::GraphicsCommandBuffer* targetCommandBuffer);
		void on_painter_receive_event(const DopeEngine::ApplicationEvent* event);
	private:
		DopeEngine::GUIRenderer* Renderer;
	};


}