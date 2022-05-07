#pragma once
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKCommandBuffer : public CommandBuffer
	{
	public:
		VKCommandBuffer(VKGraphicsDevice* device);
		virtual ~VKCommandBuffer() override;

	protected:
		// Inherited via CommandBuffer
		virtual void lock_impl() override;
		virtual void unlock_impl() override;
		virtual void clear_cached_state_impl() override;
		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) override;
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) override;
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) override;
		virtual void set_render_pass_impl(const RenderPass* renderPass) override;
		virtual void clear_color_impl(const ColorRgbaByte& color) override;
		virtual void clear_depth_impl(const float depth) override;
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) override;
		virtual void indexed_draw_call_impl(const unsigned int count) override;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkCommandBuffer BaseCommandBuffer;
	};


}