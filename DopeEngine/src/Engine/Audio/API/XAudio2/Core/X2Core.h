#pragma once
#include <xaudio2.h>
#include <x3daudio.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
template<typename T>
using X2PTR = ComPtr<T>;
typedef IXAudio2MasteringVoice X2Device;
typedef IXAudio2 X2Engine;

namespace DopeEngine
{
	class X2AudioDevice;
}