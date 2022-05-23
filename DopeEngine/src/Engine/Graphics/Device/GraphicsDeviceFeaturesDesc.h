#pragma once
#include <Engine/Math/Vector3i.h>

namespace DopeEngine
{

	/// <summary>
	/// Required fields to create a GraphicsDeviceFeatures
	/// </summary>
	struct DOPE_ENGINE_API GraphicsDeviceFeaturesDesc
	{
		static void debug_log_desc(const GraphicsDeviceFeaturesDesc& desc);

		GraphicsDeviceFeaturesDesc() :
		ComputeShader(true),GeometryShader(true),TesellationShader(true),MultipleViewports(false),ShadingRate(false),CanDisplay(true),
		MaxTexture1DDimension(1024), MaxTexture2DDimension(1024), MaxTexture3DDimension(256),MaxCubeTextureDimension(1024),
		MaxColorAttachments(4),MaxPerShaderStageResources(0),MaxComputeWorkGroupCount(Vector3i(0,0,0)),MaxComputeWorkGroupInvocations(4),MaxComputeWorkGroupSize(Vector3i(0,0,0)),
		MaxDrawCallIndexCount(0),MaxFramebufferWidth(1024),MaxFramebufferHeight(1024) {}
		~GraphicsDeviceFeaturesDesc() = default;

		bool ComputeShader;
		bool GeometryShader;
		bool TesellationShader;
		bool MultipleViewports;
		bool ShadingRate;
		bool CanDisplay;
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