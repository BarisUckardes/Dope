#include "CommandBuffer.h"
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/Resource/ResourceTypeUtils.h>
#include <Engine/Graphics/Resource/ResourceLayout.h>
#include <Engine/Graphics/Resource/ResourceView.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	void CommandBuffer::lock()
	{
		/*
		* Clear cached state
		*/
		clear_cached_state();

		/*
		* Call impl
		*/
		lock_impl();
	}
	void CommandBuffer::unlock()
	{
		/*
		* Call impl
		*/
		unlock_impl();
	}
	void CommandBuffer::set_vertex_buffer(const VertexBuffer* vertexBuffer)
	{
		set_vertex_buffer_impl(vertexBuffer);
	}

	void CommandBuffer::set_index_buffer(const IndexBuffer* indexBuffer)
	{
		set_index_buffer_impl(indexBuffer);
	}
	void CommandBuffer::set_uniform_buffer(const UniformBuffer* buffer)
	{
		set_uniform_buffer_impl(buffer);
	}

	void CommandBuffer::set_render_pass(const RenderPass* renderPass)
	{
		set_render_pass_impl(renderPass);
		CurrentBoundRenderPass = renderPass;
	}

	void CommandBuffer::clear_color(const ColorRgbaByte& color)
	{
		clear_color_impl(color);
	}
	void CommandBuffer::clear_depth(const float depth)
	{
		clear_depth_impl(depth);
	}
	void CommandBuffer::set_resource_view(const unsigned int slot, const ResourceView* view)
	{
#ifdef _DEBUG
		/*
		* Validate pipeline
		*/
		ASSERT(get_bound_render_pass(), "CommandBuffer", "You must first set a RenderPass in order to set resource views! ");

		/*
		* Validate slot length and resources
		*/
		const Array<ResourceLayout*> layouts = CurrentBoundRenderPass->get_resource_layouts_fast();
		const unsigned int resourceSlotCount = layouts.get_cursor();
		ASSERT(slot < CurrentBoundRenderPass->get_resource_layouts_fast().get_cursor(), "CommandBuffer", "You bound a resource view to slot %d, whereas there is only %d slots defined for this pipeline!", slot, resourceSlotCount);

		/*
		* Get layout variables
		*/
		const ResourceLayout* targetLayout = layouts[slot];
		const ResourceDescription targetResourceDescription = targetLayout->get_description();
		const DeviceObject* resource = view->get_resource();

		/*
		* Get object type
		*/
		const DeviceObjectType objectType = resource->get_device_object_type();

		/*
		* Check resource layout
		*/
		const DeviceObjectType slotType = ResourceTypeUtils::get_device_object_type(targetResourceDescription.Type);
		if (objectType != slotType)
		{
			ASSERT(false, "CommandBuffer", "You binded a wrong resource to slot %d.Trying to bind resource type %d whereas slot accepts %d", slot,objectType, slotType);
			return;
		}
#endif
		set_resource_view_impl(slot, view);
	}
	void CommandBuffer::indexed_draw_call(const unsigned int count)
	{
		ASSERT(get_bound_render_pass(), "CommandBuffer", "You must first set a pipeline in order to issue a draw call! ");
		indexed_draw_call_impl(count);
	}
	unsigned int CommandBuffer::get_bound_texture_count() const
	{
		return CurrentBoundTextures;
	}
	const RenderPass* CommandBuffer::get_bound_render_pass() const
	{
		return CurrentBoundRenderPass;
	}
	unsigned int CommandBuffer::get_bound_uniformbuffer_count() const
	{
		return CurrentBoundUniformBuffers;
	}
	void CommandBuffer::increment_texture_bound_count()
	{
		CurrentBoundTextures++;
	}
	void CommandBuffer::increment_uniformbuffer_bound_count()
	{
		CurrentBoundUniformBuffers++;
	}
	void CommandBuffer::clear_cached_state()
	{
		CurrentBoundTextures = 0;
		CurrentBoundRenderPass = nullptr;
		CurrentBoundUniformBuffers = 0;
		clear_cached_state_impl();
	}
}