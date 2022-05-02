#include "GraphicsDeviceProperties.h"

namespace DopeEngine
{
	String GraphicsDeviceProperties::get_vendor() const
	{
		return Vendor;
	}

	String GraphicsDeviceProperties::get_model() const
	{
		return Model;
	}

}