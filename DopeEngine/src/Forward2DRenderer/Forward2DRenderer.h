#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class SpriteRenderableComponent;
	class SpriteObserverComponent;
	class GraphicsDevice;
	class GraphicsCommandBuffer;
	class DOPE_ENGINE_API Forward2DRenderer
	{
	public:
		Forward2DRenderer(GraphicsDevice* targetDevice,const unsigned int preAllocatedSize);
		~Forward2DRenderer();

		FORCEINLINE void register_renderable(const SpriteRenderableComponent* renderable);
		FORCEINLINE void remove_renderable(const SpriteRenderableComponent* renderable);
		FORCEINLINE void register_observer(const SpriteObserverComponent* observer);
		FORCEINLINE void remove_observer(const SpriteObserverComponent* observer);

		void render();
	private:
		Array<const SpriteRenderableComponent*> Renderables;
		Array<const SpriteObserverComponent*> Observers;
		GraphicsDevice* TargetDevice;
		GraphicsCommandBuffer* CmdBuffer;
	};

}
