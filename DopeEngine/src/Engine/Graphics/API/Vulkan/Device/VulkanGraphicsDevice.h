#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VulkanGraphicsDevice : public GraphicsDevice
	{
	public:
		VulkanGraphicsDevice(Window* ownerWindow);
		~VulkanGraphicsDevice() = default;


		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;

		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;

	private:
		void _create_vulkan_device();
		void _create_win32_vulkan_device();

	};


}