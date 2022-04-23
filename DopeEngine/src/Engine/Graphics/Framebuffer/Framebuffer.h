#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Framebuffer/FramebufferDescription.h>
#include <Engine/Graphics/Pipeline/OutputDescription.h>
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
		Framebuffer(const FramebufferDescription& description);
		virtual ~Framebuffer() = default;

		/// <summary>
		/// Returns the width in pixels
		/// </summary>
		/// <returns></returns>
		 unsigned int get_width() const;

		/// <summary>
		/// Returns the height in pixels
		/// </summary>
		/// <returns></returns>
		 unsigned int get_height() const;

		/// <summary>
		/// Returns whether this framebuffer has a depth attachment or not
		/// </summary>
		/// <returns></returns>
		 bool has_depth_attachment() const;

		/// <summary>
		/// Returns whether this is a swapchain framebuffer or not
		/// </summary>
		/// <returns></returns>
		 bool is_swapchain_framebuffer() const;

		/// <summary>
		/// Returns a reference to the attachment list
		/// </summary>
		/// <returns></returns>
		 const Array<Texture*>& get_attachments_fast() const;

		/// <summary>
		/// Returns a copy of a attachment list
		/// </summary>
		/// <returns></returns>
		 Array<Texture*> get_attachments_slow() const;

		/// <summary>
		/// Returns the depth attachment
		/// </summary>
		/// <returns></returns>
		 Texture* get_depth_attachment() const;

		/// <summary>
		/// Returns the output desc for this framebuffer
		/// </summary>
		/// <returns></returns>
		OutputDescription get_output_desc() const;
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