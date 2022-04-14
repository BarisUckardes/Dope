#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Pipeline/PipelineDescription.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic pipeline abstraction class
	/// </summary>
	class DOPE_ENGINE_API Pipeline : public DeviceObject
	{
	public:
		Pipeline(const PipelineDescription& description);
		virtual ~Pipeline() = 0 {}

		/// <summary>
		/// Returns the blending state for this pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE BlendState get_blending() const;

		/// <summary>
		/// Returns the depth function kind for this pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE DepthComparisionKind get_depth_function() const;

		/// <summary>
		/// Returns whether depth testing is enabled or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_depth_test_enabled() const;

		/// <summary>
		/// Returns whether depth writing is enabled or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_depth_write_enabled() const;

		/// <summary>
		/// Returns the front face render mode
		/// </summary>
		/// <returns></returns>
		FORCEINLINE FrontFaceMode get_front_face() const;

		/// <summary>
		/// Returns the culling face mode
		/// </summary>
		/// <returns></returns>
		FORCEINLINE FaceCullMode get_cull_mode() const;

		/// <summary>
		/// Returns the polygon fill mode
		/// </summary>
		/// <returns></returns>
		FORCEINLINE PolygonFillMode get_fill_mode() const;

		/// <summary>
		/// Returns the target primitives
		/// </summary>
		/// <returns></returns>
		FORCEINLINE PrimitiveTopology get_primitives() const;

		/// <summary>
		/// Returns the shader set
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const ShaderSet* get_shader_set() const;

		/// <summary>
		/// Returns the layout of the vertex
		/// </summary>
		/// <returns></returns>
		FORCEINLINE VertexLayoutDescription get_vertex_layout() const;

		/// <summary>
		/// Returns a reference to the resource layout list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<ResourceLayout*>& get_resource_layouts_fast() const;

		/// <summary>
		/// Returns a copy of the resource layouts
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ResourceLayout*> get_resource_layouts_slow() const;
	private:
		BlendState Blending;
		DepthComparisionKind DepthFunction;
		bool DepthTest;
		bool DepthWrite;
		FrontFaceMode FrontFace;
		FaceCullMode CullingMode;
		PolygonFillMode FillMode;
		PrimitiveTopology Primitives;
		const ShaderSet* ShaderSet;
		VertexLayoutDescription VertexLayout;
		Array<ResourceLayout*> ResourceLayouts;
	};


}