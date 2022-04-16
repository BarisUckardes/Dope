#include "WindowsPortableDeviceEnumarator.h"
#include <Engine/Core/Assert.h>
#include <Windows.h>
#include <PortableDeviceApi.h>
#include <atlbase.h>
#include <wrl/client.h>
namespace DopeEngine
{
	Array<PortableDeviceInformation> WindowsPortableDeviceEnumarator::enumarate_devices() const
	{
		
		/*
		* Initialize com libray
		*/
		CoInitialize(NULL);

		/*
		* Create portable device manager
		*/
		Microsoft::WRL::ComPtr<IPortableDeviceManager> deviceManager;
		HRESULT portableDeviceCreateState =
			CoCreateInstance(CLSID_PortableDeviceManager,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(&deviceManager));
		
		/*
		* Validate portable device create state
		*/
		ASSERT(!FAILED(portableDeviceCreateState),
			"WindowsPortableDeviceManager",
			"Device manager instance creation failed!");

		/*
		* Get device count
		*/
		unsigned long deviceCount = 0;
		HRESULT getDeviceCountState = deviceManager->GetDevices(NULL, &deviceCount);

		/*
		* Validate get device count state
		*/
		ASSERT(!FAILED(getDeviceCountState),
			"WindowsPortableDeviceManager",
			"Device manager could not collect the device count!");

		/*
		* Validate device count
		*/
		if (deviceCount == 0)
			return Array<PortableDeviceInformation>();

		/*
		 Collect devices
		*/
		PWSTR* deviceIDs = new PWSTR[deviceCount];
		HRESULT collectDevicesState = deviceManager->GetDevices(deviceIDs, &deviceCount);
		
		/*
		* Validate device collect devices state
		*/
		ASSERT(!FAILED(collectDevicesState),
			"WindowsPortableDeviceManager",
			"Device manager could not collect the devices!");

		/*
		* Iterate devices
		*/
		for (unsigned long i = 0; i < deviceCount; i++)
		{
			/*
			* Colect infromation
			*/
			DWORD manufacturerLength = 0;
			DWORD friendlyNameLength = 0;
			DWORD descriptionLength = 0;
			deviceManager->GetDeviceManufacturer(deviceIDs[i], nullptr, &manufacturerLength);
			deviceManager->GetDeviceFriendlyName(deviceIDs[i], nullptr, &friendlyNameLength);
			deviceManager->GetDeviceDescription(deviceIDs[i], nullptr, &descriptionLength);

			PWSTR manufacturerName = new WCHAR[manufacturerLength];
			PWSTR friendlyName = new WCHAR[friendlyNameLength];
			PWSTR description = new WCHAR[descriptionLength];
			deviceManager->GetDeviceManufacturer(deviceIDs[i], manufacturerName, &manufacturerLength);
			deviceManager->GetDeviceFriendlyName(deviceIDs[i], friendlyName, &friendlyNameLength);
			deviceManager->GetDeviceDescription(deviceIDs[i], description, &descriptionLength);
		}

		return Array<PortableDeviceInformation>();
	}
}

