#pragma once
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	/// <summary>
	/// OpenGL implementaiton of the texture2D
	/// </summary>
	class DOPE_ENGINE_API OpenGLTexture2D final : public Texture
	{
	public:
		OpenGLTexture2D(const TextureDescription& description, DEVICE device);
		virtual ~OpenGLTexture2D() override final;

		/// <summary>
		/// Returns the texture handle
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TEXTURE_HANDLE get_handle() const;

		virtual void update(const Byte* data) override;
	private:
		void create_texture();
		void invalidate();
	private:
		TEXTURE_HANDLE Handle;
		DEVICE Device;
	};
}