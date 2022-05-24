#include "Forward2DRenderer.h"
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>

namespace DopeEngine
{
	Forward2DRenderer::Forward2DRenderer(GraphicsDevice* targetDevice,const unsigned int preAllocatedSize)
	{
		TargetDevice = targetDevice;
		Renderables.reserve(preAllocatedSize);
		Observers.reserve(preAllocatedSize);

		CmdBuffer = TargetDevice->create_command_buffer();
	}

	Forward2DRenderer::~Forward2DRenderer()
	{

	}

	void Forward2DRenderer::register_renderable(const SpriteRenderableComponent* renderable)
	{
		Renderables.add(renderable);
	}

	void Forward2DRenderer::remove_renderable(const SpriteRenderableComponent* renderable)
	{
		Renderables.remove(renderable);
	}

	void Forward2DRenderer::register_observer(const SpriteObserverComponent* observer)
	{
		Observers.add(observer);
	}

	void Forward2DRenderer::remove_observer(const SpriteObserverComponent* observer)
	{
		Observers.remove(observer);
	}

	void Forward2DRenderer::render()
	{

	}
}