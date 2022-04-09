#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API Directx12GraphicsDevice : public GraphicsDevice
	{
	public:
		Directx12GraphicsDevice(Window* ownerWindow);
		~Directx12GraphicsDevice();
		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
	private:
		void _create_directx12_device();
		void _create_win32_directx12_device();

		
	};


}