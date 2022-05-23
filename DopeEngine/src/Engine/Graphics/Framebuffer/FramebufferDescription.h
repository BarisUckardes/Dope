#pragma once
#include <Engine/Graphics/Framebuffer/FramebufferAttachmentDescription.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	/// <summary>
	/// Description for creating a framebuffer
	/// </summary>
	struct DOPE_ENGINE_API FramebufferDescription
	{
		FramebufferDescription(const unsigned int width,const unsigned int height,
			const bool createDepthAttachment,const TextureFormat depthAttachmentFormat
			,const Array<FramebufferAttachmentDescription>& attachmentDescriptions) : Width(width),Height(height),
			CreateDepthAttachment(createDepthAttachment),DepthAttachmentFormat(depthAttachmentFormat),
			AttachmentDescriptions(attachmentDescriptions) {}
		FramebufferDescription() : Width(0),Height(0),CreateDepthAttachment(false),DepthAttachmentFormat(TextureFormat::R8unorm),AttachmentDescriptions() {}
		~FramebufferDescription() = default;

		unsigned int Width;
		unsigned int Height;
		bool CreateDepthAttachment;
		TextureFormat DepthAttachmentFormat;
		Array<FramebufferAttachmentDescription> AttachmentDescriptions;
	};
}