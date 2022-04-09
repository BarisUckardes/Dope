#include "Directx12GraphicsDevice.h"
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	Directx12GraphicsDevice::Directx12GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_directx12_device();
	}
	Directx12GraphicsDevice::~Directx12GraphicsDevice()
	{

	}
	void Directx12GraphicsDevice::_create_directx12_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_directx12_device();
#else
		ASSERT(false, "Directx12GraphicsDevice", "Directx12 cannot be initialized with non-windows operating system");
#endif
	}
	void Directx12GraphicsDevice::_create_win32_directx12_device()
	{
		ASSERT(false, "Directx12GraphicsDevice", "Not implemented yet!");
	}
	GraphicsAPIType Directx12GraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Directx12;
	}
	String Directx12GraphicsDevice::get_version() const
	{
		return String();
	}
	void Directx12GraphicsDevice::make_current_impl()
	{
	}
}
