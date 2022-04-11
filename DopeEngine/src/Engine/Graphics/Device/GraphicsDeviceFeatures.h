#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Contains the features which availble to the owning device
	/// </summary>
	class DOPE_ENGINE_API GraphicsDeviceFeatures final
	{
	public:
		GraphicsDeviceFeatures(const bool computeShader,const bool geometryShader,const bool tesellationShader,const bool multipleViewports) :
			ComputeShader(computeShader),GeometryShader(geometryShader),TesellationShader(tesellationShader),MultipleViewports(multipleViewports) {}
		~GraphicsDeviceFeatures() = default;

		/// <summary>
		/// Returns whether the owning device supports compute shaders or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool get_compute_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports geometry shaders or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool get_geometry_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports tesellation shader or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool get_tesellation_shader_support() const;

		/// <summary>
		/// Returns whether the owning device supports multiple viewports or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool get_multiple_viewports_support() const;

    private:
        bool ComputeShader;
        bool GeometryShader;
        bool TesellationShader;
        bool MultipleViewports;
	};


}