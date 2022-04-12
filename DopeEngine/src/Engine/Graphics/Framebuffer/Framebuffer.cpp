#include "Framebuffer.h"
#include <Engine/Graphics/Device/GraphicsDevice.h>
namespace DopeEngine
{
	Framebuffer::Framebuffer(const FramebufferDescription& description,GraphicsDevice* device)
	{
		/*
		* Initialize
		*/
		Width = description.Width;
		Height = description.Height;
		HasDepthAttachment = description.CreateDepthAttachment;
		DepthAttachment = nullptr;

		/*
		* create attachments
		*/
		create_attachments(description.AttachmentDescriptions, device);
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
	Texture* Framebuffer::get_depth_attachment() const
	{
		return DepthAttachment;
	}
	void Framebuffer::create_attachments(const Array<FramebufferAttachmentDescription>& descriptions,GraphicsDevice* device)
	{
		/*
		* Create attachment textures
		*/
		for (unsigned int i = 0; i < descriptions.get_cursor(); i++)
		{
			/*
			* Get description
			*/
			const FramebufferAttachmentDescription& desc = descriptions[i];

			/*
			* Create description
			*/

		}
	}
}