#include "OpenGLTexture.h"
#include <Engine/Graphics/API/OpenGL/Texture/OpenGLTextureUtils.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLTexture::OpenGLTexture(const TextureDescription& description, DEVICE device) : Texture(description)
	{
		Device = device;

		create_texture();
	}
	OpenGLTexture::~OpenGLTexture()
	{
		invalidate();
	}
	TEXTURE_HANDLE OpenGLTexture::get_handle() const
	{
		return Handle;
	}

	void OpenGLTexture::create_texture()
	{
		invalidate();

		const TextureFormat format = get_format();
		glGenTextures(1, &Handle);

		glBindTexture(GL_TEXTURE_2D, Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, OpenGLTextureUtils::get_internal_format(format), get_width(), get_height(), 0, OpenGLTextureUtils::get_format(format), OpenGLTextureUtils::get_data_type(format), nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLTexture::invalidate()
	{
		if (Handle != GL_NONE)
		{
			glDeleteTextures(1, &Handle);
			Handle = GL_NONE;
		}
	}
}