#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>

namespace DopeEngine
{
	class GraphicsDevice;
	class GUIRenderer;
	class ApplicationEvent;
	class GraphicsCommandBuffer;
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

		/// <summary>
		/// Starts the painter rendering session
		/// </summary>
		void StartRendering();

		/// <summary>
		/// Finalizes the painter rendering session and renders the draw data
		/// </summary>
		void FinalizeRendering(const DopeEngine::GraphicsCommandBuffer* targetCommandBuffer);

		/// <summary>
		/// Called when painter receives an event
		/// </summary>
		/// <param name="event"></param>
		void on_painter_receive_event(const DopeEngine::ApplicationEvent* event);
	private:
		DopeEngine::GUIRenderer* Renderer;
	};


}