#pragma once
#include <Engine/World/WorldFunction.h>
#include <Engine/Structures/Array.h>

namespace DopeEngine
{
	class SpriteRenderableComponent;
	class SpriteObserverComponent;

	/// <summary>
	/// World function responsible for listening the sprite renderables and sprite observers and also renders them
	/// </summary>
	class DOPE_ENGINE_API Forward2DRendererWorldFunction : public WorldFunction
	{
		GENERATE_WORLD_FUNCTION(Forward2DRendererWorldFunction);
	public:

		void register_sprite_renderable(const SpriteRenderableComponent* renderable);
		void remove_sprite_renderable(const SpriteRenderableComponent* renderable);
		void register_sprite_observer(const SpriteObserverComponent* observer);
		void remove_sprite_observer(const SpriteObserverComponent* observer);

		// Inherited via WorldFunction
		virtual void register_component(Component* component) override;
		virtual void remove_component(Component* component) override;
		virtual void initialize() override;
		virtual void execute() override;
		virtual void finalize() override;
	private:
		Array<const SpriteRenderableComponent*> Renderables;
		Array<const SpriteObserverComponent*> Observers;
	};
}