#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

namespace DopeEngine
{
	class DOPE_ENGINE_API DX11GraphicsDevice : public GraphicsDevice
	{
	public:
		DX11GraphicsDevice(Window* ownerWindow);
		~DX11GraphicsDevice() = default;
		
		ComPtr<ID3D11Device> get_dx11_device() const;
		ComPtr<ID3D11DeviceContext> get_dx11_immediate_context() const;
		ComPtr<ID3D11RenderTargetView> get_swawpchain_rtv() const;


		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(GraphicsDeviceObject* object) override;
		virtual GraphicsBuffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual RenderPass* create_render_pass_impl(const RenderPassDesc& desc) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc* desc) const override;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription& description) override;
		virtual void update_buffer_impl(GraphicsBuffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer) override;
	private:
		void _create_directx11_device();
		void _create_win32_directx11_device();
	private:
		DXPTR<IDXGISwapChain> SwapChain;
		DXPTR<ID3D11Device> Device;
		DXPTR<ID3D11DeviceContext> ImmediateContext;
		DXPTR<ID3D11DeviceContext> DeferredContext;
		DXPTR<ID3D11RenderTargetView> SwapchainRenderTargetView;

		// Inherited via GraphicsDevice
		virtual void wait_for_finish_impl() override;

		// Inherited via GraphicsDevice
		virtual bool does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages) override;
	};


}