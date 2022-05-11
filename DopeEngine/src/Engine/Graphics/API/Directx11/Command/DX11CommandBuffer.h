#pragma once
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
#include <Engine/Graphics/Shader/ShaderType.h>
namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11CommandBuffer : public CommandBuffer
	{
	public:
		DX11CommandBuffer(DX11GraphicsDevice* device);
		virtual ~DX11CommandBuffer() final override;

	protected:
		// Inherited via CommandBuffer
		virtual void unlock_impl() override;
		virtual void clear_cached_state_impl() override;
		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) override;
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) override;
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) override;
		virtual void start_render_pass_impl(const RenderPass* renderPass) override;
		virtual void set_viewport_desc_impl(const ViewportDesc& desc) override final;
		virtual void set_scissors_desc_impl(const ScissorsDesc& desc) override final;
		virtual void clear_color_impl(const ColorRgbaByte& color) override;
		virtual void clear_depth_impl(const float depth) override;
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) override;
		virtual void indexed_draw_call_impl(const unsigned int count) override;
		virtual void lock_impl();
	private:
		 void set_constant_buffer(const GraphicsBuffer* buffer,const ShaderType stage);
		 void set_shader_resource(const ResourceView* view, const ShaderType stage);
	private:
		DX11GraphicsDevice* Device;
		Array <ComPtr<ID3D11RenderTargetView>> CurrentColorTargets;
		ComPtr<ID3D11DepthStencilView> CurrentDepthTarget;
		D3D11_VIEWPORT CurrentDX11Viewport;
	};


}