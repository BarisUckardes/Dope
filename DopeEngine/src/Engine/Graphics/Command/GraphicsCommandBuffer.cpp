#include "GraphicsCommandBuffer.h"
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/Resource/GraphicsResourceTypeUtils.h>
#include <Engine/Graphics/Resource/GraphicsResourceSlotDesc.h>
#include <Engine/Graphics/Resource/GraphicsResource.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	void GraphicsCommandBuffer::lock()
	{
		clear_cached_state();

		lock_impl();
	}
	void GraphicsCommandBuffer::unlock()
	{
		unlock_impl();
	}
	void GraphicsCommandBuffer::set_vertex_buffer(const VertexBuffer* vertexBuffer)
	{
		set_vertex_buffer_impl(vertexBuffer);
	}

	void GraphicsCommandBuffer::set_index_buffer(const IndexBuffer* indexBuffer)
	{
		set_index_buffer_impl(indexBuffer);
	}

	void GraphicsCommandBuffer::set_uniform_buffer(const UniformBuffer* buffer)
	{
		set_uniform_buffer_impl(buffer);
	}

	void GraphicsCommandBuffer::set_render_pass(const RenderPass* renderPass)
	{
		set_render_pass_impl(renderPass);
		CurrentBoundRenderPass = renderPass;
	}

	void GraphicsCommandBuffer::set_viewport_desc(const ViewportDesc& desc)
	{
		CurrentBoundViewportDesc = desc;
		set_viewport_desc_impl(desc);
	}

	void GraphicsCommandBuffer::set_scissors_desc(const ScissorsDesc& desc)
	{
		CurrentBoundScissorsDesc = desc;
		set_scissors_desc_impl(desc);
	}

	void GraphicsCommandBuffer::clear_color(const ColorRgbaByte& color)
	{
		clear_color_impl(color);
	}
	void GraphicsCommandBuffer::clear_depth(const float depth)
	{
		clear_depth_impl(depth);
	}
	void GraphicsCommandBuffer::commit_resource(const unsigned int slot, const GraphicsResource* resource)
	{
#ifdef _DEBUG
		ASSERT(get_bound_render_pass(), "GraphicsCommandBuffer", "You must first set a RenderPass in order to set resource views! ");

		const Array<GraphicsResourceSlotDesc> resourceSlotDesc = CurrentBoundRenderPass->get_resource_slots();
		const unsigned int resourceSlotCount = resourceSlotDesc.get_cursor();

		ASSERT(slot < resourceSlotDesc.get_cursor(), "GraphicsCommandBuffer", "You bound a resource view to slot %d, whereas there is only %d slots defined for this pipeline!", slot, resourceSlotCount);

		const GraphicsResourceSlotDesc targetSlotDesc = resourceSlotDesc[slot];
		const GraphicsDeviceObject* targetResource = resource->get_resource();
		const GraphicsDeviceObjectType objectType = resource->get_device_object_type();
		const GraphicsDeviceObjectType slotType = GraphicsResourceTypeUtils::get_device_object_type(targetSlotDesc.Type);

		if (objectType != slotType)
		{
			ASSERT(false, "GraphicsCommandBuffer", "You binded a wrong resource to slot %d.Trying to bind resource type %d whereas slot accepts %d", slot,objectType, slotType);
			return;
		}
#endif
		commit_resource_impl(slot, resource);
	}
	void GraphicsCommandBuffer::indexed_draw_call(const unsigned int count)
	{
		ASSERT(get_bound_render_pass(), "GraphicsCommandBuffer", "You must first set a RenderPass in order to issue a draw call! ");
		indexed_draw_call_impl(count);
	}
	unsigned int GraphicsCommandBuffer::get_bound_texture_count() const
	{
		return CurrentBoundTextures;
	}
	const RenderPass* GraphicsCommandBuffer::get_bound_render_pass() const
	{
		return CurrentBoundRenderPass;
	}
	ViewportDesc GraphicsCommandBuffer::get_bound_viewport_desc() const
	{
		return CurrentBoundViewportDesc;
	}
	ScissorsDesc GraphicsCommandBuffer::get_bound_scissors_desc() const
	{
		return CurrentBoundScissorsDesc;
	}
	unsigned int GraphicsCommandBuffer::get_bound_uniformbuffer_count() const
	{
		return CurrentBoundUniformBuffers;
	}
	void GraphicsCommandBuffer::increment_texture_bound_count()
	{
		CurrentBoundTextures++;
	}
	void GraphicsCommandBuffer::increment_uniformbuffer_bound_count()
	{
		CurrentBoundUniformBuffers++;
	}
	void GraphicsCommandBuffer::clear_cached_state()
	{
		CurrentBoundTextures = 0;
		CurrentBoundRenderPass = nullptr;
		CurrentBoundUniformBuffers = 0;
		clear_cached_state_impl();
	}
}