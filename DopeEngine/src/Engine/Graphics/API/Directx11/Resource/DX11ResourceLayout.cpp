#include "DX11ResourceLayout.h"

namespace DopeEngine
{
	DX11ResourceLayout::DX11ResourceLayout(const ResourceDescription& desc, DX11GraphicsDevice* device) : ResourceLayout(desc)
	{
		create(desc, device);
	}
	DX11ResourceLayout::~DX11ResourceLayout()
	{

	}
	void DX11ResourceLayout::create(const ResourceDescription& desc, DX11GraphicsDevice* device)
	{
		
	}
}