#include "GraphicsDeviceFeaturesDesc.h"
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	void GraphicsDeviceFeaturesDesc::debug_log_desc(const GraphicsDeviceFeaturesDesc& desc)
	{
		LOG("GraphicsDeviceFeaturesDesc", "Supports compute shaders: %s",desc.ComputeShader == true ? "yes":"no");
		LOG("GraphicsDeviceFeaturesDesc", "Supports geometry shaders: %s", desc.GeometryShader == true ? "yes" : "no");
		LOG("GraphicsDeviceFeaturesDesc", "Supports multiple viewports: %s", desc.MultipleViewports == true ? "yes" : "no");
		LOG("GraphicsDeviceFeaturesDesc", "Supports shading rate: %s", desc.ShadingRate == true ? "yes" : "no");
		LOG("GraphicsDeviceFeaturesDesc", "Max color attachments: %d", desc.MaxColorAttachments);
		LOG("GraphicsDeviceFeaturesDesc", "Max compute work group count: %d,%d,%d", desc.MaxComputeWorkGroupCount.X, desc.MaxComputeWorkGroupCount.Y, desc.MaxComputeWorkGroupCount.Z);
		LOG("GraphicsDeviceFeaturesDesc", "Max compute work group invocations: %d", desc.MaxComputeWorkGroupInvocations);
		LOG("GraphicsDeviceFeaturesDesc", "Max compute work group size: %d,%d,%d", desc.MaxComputeWorkGroupSize.X, desc.MaxComputeWorkGroupSize.Y, desc.MaxComputeWorkGroupSize.Z);
		LOG("GraphicsDeviceFeaturesDesc", "Max texture1D   dimension: %d", desc.MaxTexture1DDimension);
		LOG("GraphicsDeviceFeaturesDesc", "Max texture2D   dimension: %d", desc.MaxTexture2DDimension);
		LOG("GraphicsDeviceFeaturesDesc", "Max texture3D   dimension: %d", desc.MaxTexture3DDimension);
		LOG("GraphicsDeviceFeaturesDesc", "Max cubetexture dimension: %d", desc.MaxCubeTextureDimension);
		LOG("GraphicsDeviceFeaturesDesc", "Max draw call index count: %d", desc.MaxDrawCallIndexCount);
		LOG("GraphicsDeviceFeaturesDesc", "Max framebuffer width: %d", desc.MaxFramebufferWidth);
		LOG("GraphicsDeviceFeaturesDesc", "Max framebuffer height: %d", desc.MaxFramebufferHeight);
		LOG("GraphicsDeviceFeaturesDesc", "Max shader stage resources: %d", desc.MaxPerShaderStageResources);
	}

}

