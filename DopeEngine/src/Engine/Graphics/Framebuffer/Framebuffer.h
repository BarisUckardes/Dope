#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Framebuffer/FramebufferDescription.h>
namespace DopeEngine
{
	class Texture;

	/// <summary>
	/// Graphics api agnostic framebuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API Framebuffer : public DeviceObject
	{
	public:
		Framebuffer(const FramebufferDescription& description);
		virtual ~Framebuffer() = default;

		/// <summary>
		/// Returns the width in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the height in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_height() const;

		/// <summary>
		/// Returns whether this framebuffer has a depth attachment or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_depth_attachment() const;

		/// <summary>
		/// Returns a reference to the attachment list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Texture*>& get_attachments_fast() const;

		/// <summary>
		/// Returns a copy of a attachment list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Texture*> get_attachments_slow() const;
	private:
		unsigned int Width;
		unsigned int Height;
		bool HasDepthAttachment;
		Array<Texture*> Attachments;
	};
}