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

		/// <summary>
		/// Whether supports compute shader or not
		/// </summary>
		bool ComputeShader;

		/// <summary>
		/// Whether supports geometry shader or not
		/// </summary>
		bool GeometryShader;

		/// <summary>
		/// Whether supports tesellation shader or not
		/// </summary>
		bool TesellationShader;

		/// <summary>
		/// Whether supports multiple viewports or not
		/// </summary>
		bool MultipleViewports;

		/// <summary>
		/// Whether supports variable shading rates or not
		/// </summary>
		bool ShadingRate;

		/// <summary>
		/// Whether supports outputting to a swapchain or not
		/// </summary>
		bool CanDisplay;
		unsigned int MaxTexture1DDimension;

		/// <summary>
		/// Max dimensions for a 1D-Texture
		/// </summary>
		unsigned int MaxTexture2DDimension;

		/// <summary>
		/// Max dimensions for a 2D-Texture
		/// </summary>
		unsigned int MaxTexture3DDimension;

		/// <summary>
		/// Max dimensions for a Cube-Texture
		/// </summary>
		unsigned int MaxCubeTextureDimension;

		/// <summary>
		/// Max count of framebuffer color attachments
		/// </summary>
		unsigned int MaxColorAttachments;

		/// <summary>
		/// Max amount of resources per shader stage
		/// </summary>
		unsigned int MaxPerShaderStageResources;

		/// <summary>
		/// Max compute shader work group counts
		/// </summary>
		Vector3i MaxComputeWorkGroupCount;

		/// <summary>
		/// Max compute shader work group invocation count
		/// </summary>
		unsigned int MaxComputeWorkGroupInvocations;

		/// <summary>
		/// Max compute shader work group sizes
		/// </summary>
		Vector3i MaxComputeWorkGroupSize;

		/// <summary>
		/// Max index count per draw call
		/// </summary>
		unsigned int MaxDrawCallIndexCount;

		/// <summary>
		/// Max framebuffer color attachment width
		/// </summary>
		unsigned int MaxFramebufferWidth;

		/// <summary>
		/// Max framebuffer color attachment height
		/// </summary>
		unsigned int MaxFramebufferHeight;
	};
}