#include "GraphicsDeviceFeatures.h"

namespace DopeEngine
{
	GraphicsDeviceFeatures::GraphicsDeviceFeatures(const GraphicsDeviceFeaturesDesc& desc)
	{
		/*
		* Initialize
		*/
		ComputeShader = desc.ComputeShader;
		GeometryShader = desc.GeometryShader;
		TesellationShader = desc.TesellationShader;
		MultipleViewports = desc.MultipleViewports;
		ShadingRate = desc.ShadingRate;
		MaxTexture1DDimension = desc.MaxTexture1DDimension;
		MaxTexture2DDimension = desc.MaxTexture2DDimension;
		MaxTexture3DDimension = desc.MaxTexture3DDimension;
		MaxCubeTextureDimension = desc.MaxCubeTextureDimension;
		MaxColorAttachments = desc.MaxColorAttachments;
		MaxPerShaderStageResources = desc.MaxPerShaderStageResources;
		MaxComputeWorkGroupCount = desc.MaxComputeWorkGroupCount;
		MaxComputeWorkGroupSize = desc.MaxComputeWorkGroupSize;
		MaxDrawCallIndexCount = desc.MaxDrawCallIndexCount;
		MaxFramebufferWidth = desc.MaxFramebufferWidth;
		MaxFramebufferHeight = desc.MaxFramebufferHeight;

	}
	bool GraphicsDeviceFeatures::has_compute_shader_support() const
	{
		return ComputeShader;
	}
	bool GraphicsDeviceFeatures::has_geometry_shader_support() const
	{
		return GeometryShader;
	}
	bool GraphicsDeviceFeatures::has_tesellation_shader_support() const
	{
		return TesellationShader;
	}
	bool GraphicsDeviceFeatures::has_multiple_viewports_support() const
	{
		return MultipleViewports;
	}
	bool GraphicsDeviceFeatures::has_shading_rate_support() const
	{
		return ShadingRate;
	}
	unsigned int GraphicsDeviceFeatures::get_max_texture1D_dimension() const
	{
		return MaxTexture1DDimension;
	}

	unsigned int GraphicsDeviceFeatures::get_max_texture2D_dimension() const
	{
		return MaxTexture2DDimension;
	}

	unsigned int GraphicsDeviceFeatures::get_max_texture3D_dimension() const
	{
		return MaxTexture3DDimension;
	}

	unsigned int GraphicsDeviceFeatures::get_max_cubeTexture_dimension() const
	{
		return MaxCubeTextureDimension;
	}

	unsigned int GraphicsDeviceFeatures::get_max_color_attachments() const
	{
		return MaxColorAttachments;
	}

	unsigned int GraphicsDeviceFeatures::get_max_per_shader_stage_resources() const
	{
		return MaxPerShaderStageResources;
	}

	Vector3i GraphicsDeviceFeatures::get_compute_work_group_count() const
	{
		return MaxComputeWorkGroupCount;
	}

	unsigned int GraphicsDeviceFeatures::get_compute_work_group_invocations() const
	{
		return MaxComputeWorkGroupInvocations;
	}

	Vector3i GraphicsDeviceFeatures::get_compute_work_group_size() const
	{
		return MaxComputeWorkGroupSize;
	}

	unsigned int GraphicsDeviceFeatures::get_max_draw_call_index_count() const
	{
		return MaxDrawCallIndexCount;
	}

	unsigned int GraphicsDeviceFeatures::get_max_framebuffer_width() const
	{
		return MaxFramebufferWidth;
	}

	unsigned int GraphicsDeviceFeatures::get_max_framebuffer_height() const
	{
		return MaxFramebufferHeight;
	}

}