#include "OpenGLFramebuffer.h"
#include <Engine/Graphics/API/OpenGL/Texture/OpenGLTexture.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferDescription& description, DEVICE device) : Framebuffer(description)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* create 
		*/
		create();
	}
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		invalidate();
	}
	FRAMEBUFFER_HANDLE OpenGLFramebuffer::get_handle() const
	{
		return Handle;
	}
	void OpenGLFramebuffer::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle == GL_NONE)
		{
			glDeleteFramebuffers(1, &Handle);
			Handle = GL_NONE;
		}
	}
	void OpenGLFramebuffer::create()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create
		*/
		glCreateFramebuffers(1, &Handle);

		/*
		* Attach framebuffer attachments
		*/
		glBindFramebuffer(GL_FRAMEBUFFER, Handle);

		FRAMEBUFFER_ATTACHMENT attachment = GL_COLOR_ATTACHMENT0;
		const Array<Texture*> attachments = get_attachments_fast();
		Array<FRAMEBUFFER_ATTACHMENT> colorAttachmentFlags;
		for (unsigned int i = 0; attachments.get_cursor(); i++)
		{
			/*
			* Get texture as opengl texture
			*/
			const OpenGLTexture* texture = (const OpenGLTexture*)attachments[i];

			/*
			* Attach
			*/
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->get_handle(), 0);

			/*
			* Save the color attachment flag and increment attachment slot
			*/
			colorAttachmentFlags.add(attachment);
			attachment++;
		}

		/*
		* Validate and attach depth attachment
		*/
		if (has_depth_attachment())
		{
			/*
			* Get depth attachment as opengl texture
			*/
			const OpenGLTexture* depthAttachment = (const OpenGLTexture*)get_depth_attachment();

			/*
			* Attach depth
			*/
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthAttachment->get_handle(), 0);
		}
		
		/*
		* Set draw buffers
		*/
		glDrawBuffers(colorAttachmentFlags.get_cursor(), colorAttachmentFlags.get_data());

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}
}