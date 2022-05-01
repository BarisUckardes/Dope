#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Math/Vector3i.h>
#include <Engine/Graphics/Device/GraphicsDeviceFeaturesDesc.h>
namespace DopeEngine
{
	/// <summary>
	/// Contains the features which availble to the owning device
	/// </summary>
	class DOPE_ENGINE_API GraphicsDeviceFeatures
	{
	public:
		GraphicsDeviceFeatures(const GraphicsDeviceFeaturesDesc& desc);
		~GraphicsDeviceFeatures() = default;

		/// <summary>
		/// Returns whether the owning device supports compute shaders or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_compute_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports geometry shaders or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_geometry_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports tesellation shader or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_tesellation_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports multiple viewports or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_multiple_viewports_support() const;

		/// <summary>
		/// Returns whether the device supports shading rate
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_shading_rate_support() const;

		FORCEINLINE unsigned int get_max_texture1D_dimension() const;
		FORCEINLINE unsigned int get_max_texture2D_dimension() const;
		FORCEINLINE unsigned int get_max_texture3D_dimension() const;
		FORCEINLINE unsigned int get_max_cubeTexture_dimension() const;
		FORCEINLINE unsigned int get_max_color_attachments() const;
		FORCEINLINE unsigned int get_max_per_shader_stage_resources() const;
		FORCEINLINE Vector3i get_compute_work_group_count() const;
		FORCEINLINE unsigned int get_compute_work_group_invocations() const;
		FORCEINLINE Vector3i get_compute_work_group_size() const;
		FORCEINLINE unsigned int get_max_draw_call_index_count() const;
		FORCEINLINE unsigned int get_max_framebuffer_width() const;
		FORCEINLINE unsigned int get_max_framebuffer_height() const;
    private:
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