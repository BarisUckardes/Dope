#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/Framebuffer/FramebufferDescription.h>
namespace DopeEngine
{
	class Texture;
	class GraphicsDevice;
	/// <summary>
	/// Graphics api agnostic framebuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API Framebuffer : public GraphicsDeviceObject
	{
		friend class SwapchainFramebuffer;
	public:
		Framebuffer(const FramebufferDescription& description);
		~Framebuffer() = default;

		FORCEINLINE unsigned int get_width() const;
		FORCEINLINE unsigned int get_height() const;
		FORCEINLINE bool has_depth_attachment() const;
		FORCEINLINE bool is_swapchain_framebuffer() const;
		FORCEINLINE const Array<Texture*>& get_attachments_fast() const;
		FORCEINLINE Array<Texture*> get_attachments_slow() const;
		FORCEINLINE Texture* get_depth_attachment() const;
	private:
		static void _set_width(Framebuffer* buffer, const unsigned int width);
		static void _set_height(Framebuffer* buffer, const unsigned int height);
		static void _mark_swapchain(Framebuffer* buffer);
	private:
		unsigned int Width;
		unsigned int Height;
		bool HasDepthAttachment;
		bool Swapchain;
		Array<Texture*> Attachments;
		Texture* DepthAttachment;
	};
}