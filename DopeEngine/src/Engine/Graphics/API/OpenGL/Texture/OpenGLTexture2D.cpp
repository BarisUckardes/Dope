#include "OpenGLTexture2D.h"
#include <Engine/Graphics/API/OpenGL/Texture/OpenGLTextureUtils.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLTexture2D::OpenGLTexture2D(const TextureDescription& description, DEVICE device) : Texture(description)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* Create texture
		*/
		create_texture();
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		invalidate();
	}
	TEXTURE_HANDLE OpenGLTexture2D::get_handle() const
	{
		return Handle;
	}
	void OpenGLTexture2D::update(const Byte* data)
	{
		/*
		* Update texture data region
		*/
		const TextureFormat format = get_format();
		glBindTexture(GL_TEXTURE_2D, Handle);
		glTextureSubImage2D(Handle, 0, 0, 0, get_width(), get_height(), OpenGLTextureUtils::get_format(format), OpenGLTextureUtils::get_data_type(format), data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLTexture2D::create_texture()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create and allocate texture
		*/
		const TextureFormat format = get_format();
		glCreateTextures(GL_TEXTURE_2D, 1, &Handle);
		glBindTexture(GL_TEXTURE_2D, Handle);
		glTexImage2D(GL_TEXTURE_2D, 0, OpenGLTextureUtils::get_internal_format(format), get_width(), get_height(), 0, OpenGLTextureUtils::get_format(format), OpenGLTextureUtils::get_data_type(format), nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLTexture2D::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle != GL_NONE)
		{
			glDeleteTextures(1, &Handle);
			Handle = GL_NONE;
		}
	}
}