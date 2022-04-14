#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Framebuffer/FramebufferDescription.h>
namespace DopeEngine
{
	class Texture;
	class GraphicsDevice;
	/// <summary>
	/// Graphics api agnostic framebuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API Framebuffer : public DeviceObject
	{
		friend class SwapchainFramebuffer;
	public:
		Framebuffer(const FramebufferDescription& description,GraphicsDevice* device);
		virtual ~Framebuffer() = default;

		/// <summary>
		/// Returns the width in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the height in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_height() const;

		/// <summary>
		/// Returns whether this framebuffer has a depth attachment or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_depth_attachment() const;

		/// <summary>
		/// Returns whether this is a swapchain framebuffer or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_swapchain_framebuffer() const;

		/// <summary>
		/// Returns a reference to the attachment list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Texture*>& get_attachments_fast() const;

		/// <summary>
		/// Returns a copy of a attachment list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Texture*> get_attachments_slow() const;

		/// <summary>
		/// Returns the depth attachment
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Texture* get_depth_attachment() const;
	private:
		static void _set_width(Framebuffer* buffer, const unsigned int width);
		static void _set_height(Framebuffer* buffer, const unsigned int height);
		static void _mark_swapchain(Framebuffer* buffer);
		void create_attachments(const Array<FramebufferAttachmentDescription>& descriptions, GraphicsDevice* device);
	private:
		unsigned int Width;
		unsigned int Height;
		bool HasDepthAttachment;
		bool Swapchain;
		Array<Texture*> Attachments;
		Texture* DepthAttachment;
	};
}