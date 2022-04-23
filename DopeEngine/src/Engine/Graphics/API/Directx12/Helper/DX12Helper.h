#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12Helper
	{
	public:
		DX12Helper() = delete;
		~DX12Helper() = delete;

		static void offset_rtv_handle(const unsigned int offset, const unsigned int incrementSize, D3D12_CPU_DESCRIPTOR_HANDLE& handle);
		
	};
}