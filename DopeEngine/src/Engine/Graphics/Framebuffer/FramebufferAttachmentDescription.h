#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for a framebuffer attachment
	/// </summary>
	struct DOPE_ENGINE_API FramebufferAttachmentDescription
	{
		FramebufferAttachmentDescription(const TextureFormat format) : Format(format) {}
		FramebufferAttachmentDescription() = default;
		~FramebufferAttachmentDescription() = default;

		/// <summary>
		/// The format of the framebuffer attachments
		/// </summary>
		TextureFormat Format;
	};

}

