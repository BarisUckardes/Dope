#pragma once
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
template<typename T>
using DXPTR = ComPtr<T>;
namespace DopeEngine
{
	class DX12GraphicsDevice;
}