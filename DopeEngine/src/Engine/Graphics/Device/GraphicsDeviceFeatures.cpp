#include "GraphicsDeviceFeatures.h"

namespace DopeEngine
{
	bool GraphicsDeviceFeatures::get_compute_shader_support() const
	{
		return ComputeShader;
	}
	bool GraphicsDeviceFeatures::get_geometry_shader_support() const
	{
		return GeometryShader;
	}
	bool GraphicsDeviceFeatures::get_tesellation_shader_support() const
	{
		return TesellationShader;
	}
	bool GraphicsDeviceFeatures::get_multiple_viewports_support() const
	{
		return MultipleViewports;
	}
}