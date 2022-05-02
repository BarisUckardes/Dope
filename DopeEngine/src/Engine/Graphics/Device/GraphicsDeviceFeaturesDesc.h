#pragma once
#include <Engine/Math/Vector3i.h>

namespace DopeEngine
{

	struct DOPE_ENGINE_API GraphicsDeviceFeaturesDesc
	{
		static void debug_log_desc(const GraphicsDeviceFeaturesDesc& desc);

		GraphicsDeviceFeaturesDesc() :
		ComputeShader(true),GeometryShader(true),TesellationShader(true),MultipleViewports(false),ShadingRate(false),
		MaxTexture1DDimension(4096), MaxTexture2DDimension(4096), MaxTexture3DDimension(4096),MaxCubeTextureDimension(4096),
		MaxColorAttachments(4),MaxPerShaderStageResources(-1),MaxComputeWorkGroupCount(Vector3i(-1,-1,-1)),MaxComputeWorkGroupInvocations(128),MaxComputeWorkGroupSize(Vector3i(-1,-1,-1)),
		MaxDrawCallIndexCount(-1),MaxFramebufferWidth(4096),MaxFramebufferHeight(4096) {}
		~GraphicsDeviceFeaturesDesc() = default;

		bool		 ComputeShader;
		bool		 GeometryShader;
		bool		 TesellationShader;
		bool		 MultipleViewports;
		bool		 ShadingRate;
		unsigned int MaxTexture1DDimension;
		unsigned int MaxTexture2DDimension;
		unsigned int MaxTexture3DDimension;
		unsigned int MaxCubeTextureDimension;
		unsigned int MaxColorAttachments;
		unsigned int MaxPerShaderStageResources;
		Vector3i MaxComputeWorkGroupCount;
		unsigned int MaxComputeWorkGroupInvocations;
		Vector3i MaxComputeWorkGroupSize;
		unsigned int MaxDrawCallIndexCount;
		unsigned int MaxFramebufferWidth;
		unsigned int MaxFramebufferHeight;
	};
}