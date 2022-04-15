#include "Framebuffer.h"
#include <Engine/Graphics/Device/GraphicsDevice.h>
namespace DopeEngine
{
	Framebuffer::Framebuffer(const FramebufferDescription& description) : DeviceObject(DeviceObjectType::Framebuffer)
	{
		/*
		* Initialize
		*/
		Width = description.Width;
		Height = description.Height;
		HasDepthAttachment = description.CreateDepthAttachment;
		DepthAttachment = nullptr;
		Swapchain = false;

	}
	unsigned int Framebuffer::get_width() const
	{
		return Width;
	}
	unsigned int Framebuffer::get_height() const
	{
		return Height;
	}
	bool Framebuffer::has_depth_attachment() const
	{
		return HasDepthAttachment;
	}
	bool Framebuffer::is_swapchain_framebuffer() const
	{
		return Swapchain;
	}
	const Array<Texture*>& Framebuffer::get_attachments_fast() const
	{
		return Attachments;
	}
	Array<Texture*> Framebuffer::get_attachments_slow() const
	{
		return Attachments;
	}
	Texture* Framebuffer::get_depth_attachment() const
	{
		return DepthAttachment;
	}
	void Framebuffer::_set_width(Framebuffer* buffer, const unsigned int width)
	{
		buffer->Width = width;
	}
	void Framebuffer::_set_height(Framebuffer* buffer, const unsigned int height)
	{
		buffer->Height = height;
	}
	void Framebuffer::_mark_swapchain(Framebuffer* buffer)
	{
		buffer->Swapchain = true;
	}
	
}