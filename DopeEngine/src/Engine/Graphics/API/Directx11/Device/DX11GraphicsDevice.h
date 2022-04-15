#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

namespace DopeEngine
{
	class DOPE_ENGINE_API DX11GraphicsDevice : public GraphicsDevice
	{
	public:
		DX11GraphicsDevice(Window* ownerWindow);
		~DX11GraphicsDevice() = default;
		
		FORCEINLINE ID3D11Device* get_dx11_device() const;
		FORCEINLINE ID3D11DeviceContext* get_dx11_immediate_context() const;
		FORCEINLINE ID3D11DeviceContext* get_dx11_deferred_context() const;
		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(DeviceObject* object) override;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const override;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceLayoutDescription& description) override;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription& description) override;
		virtual void update_buffer_impl(Buffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		virtual void swap_swapchain_buffers_impl() override;
	private:
		void _create_directx11_device();
		void _create_win32_directx11_device();
	private:
		IDXGISwapChain* SwapChain;
		ID3D11Device* Device;
		ID3D11DeviceContext* ImmediateContext;
		ID3D11DeviceContext* DeferredContext;
		ID3D11RenderTargetView* SwapchainRenderTargetView;
	};


}