#include "Directx11GraphicsDevice.h"
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	Directx11GraphicsDevice::Directx11GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_directx11_device();
	}
	void Directx11GraphicsDevice::_create_directx11_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_win32_directx11_device();
#else
		ASSERT(false,"Directx11GraphicsDevice", "Directx11 cannot be initialized with non-windows operating system");
#endif
	}
	void Directx11GraphicsDevice::_create_win32_directx11_device()
	{
		ASSERT(false,"Directx11GraphicsDevice", "Not implemented yet!");
	}
	GraphicsAPIType Directx11GraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Directx11;
	}
	String Directx11GraphicsDevice::get_version() const
	{
		return String();
	}
	void Directx11GraphicsDevice::make_current_impl()
	{
	}
}