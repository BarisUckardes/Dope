#include "Framebuffer.h"

namespace DopeEngine
{
	Framebuffer::Framebuffer(const FramebufferDescription& description)
	{

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
	const Array<Texture*>& Framebuffer::get_attachments_fast() const
	{
		return Attachments;
	}
	Array<Texture*> Framebuffer::get_attachments_slow() const
	{
		return Attachments;
	}
}