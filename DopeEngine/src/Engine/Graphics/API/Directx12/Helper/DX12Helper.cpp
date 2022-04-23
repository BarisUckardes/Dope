#include "DX12Helper.h"

namespace DopeEngine
{
	void DX12Helper::offset_rtv_handle(const unsigned int offset,const unsigned int incrementSize, D3D12_CPU_DESCRIPTOR_HANDLE& handle)
	{
		handle.ptr = SIZE_T(INT64(handle.ptr) + INT64(offset) * INT64(incrementSize));
	}

}