#pragma once
#include <d3d11.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
template<typename T>
using DXPTR = ComPtr<T>;
namespace DopeEngine
{
	class DX11GraphicsDevice;
}
void _handle_error(HRESULT h);
#define DXERROR(h) _handle_error(h);
