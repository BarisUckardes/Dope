#include "Pipeline.h"

namespace DopeEngine
{
	Pipeline::Pipeline(const PipelineDescription& description) : DeviceObject(DeviceObjectType::Pipeline)
	{
		Blending = description.BlendingState;
		DepthFunction = description.DepthComparision;
		DepthTest = description.DepthTest;
		DepthWrite = description.DepthWrite;
		FrontFace = description.FrontFace;
		CullingMode = description.CullFace;
		FillMode = description.FillMode;
		Primitives = description.Primitives;
		ShaderSet = description.ShaderSet;
		VertexLayout = description.LayoutDescription;
		ResourceLayouts = description.ResourceLayouts;
	}
	BlendState Pipeline::get_blending() const
	{
		return Blending;
	}
	DepthComparisionKind Pipeline::get_depth_function() const
	{
		return DepthFunction;
	}
	bool Pipeline::is_depth_test_enabled() const
	{
		return DepthTest;
	}
	bool Pipeline::is_depth_write_enabled() const
	{
		return DepthWrite;
	}
	FrontFaceMode Pipeline::get_front_face() const
	{
		return FrontFace;
	}
	FaceCullMode Pipeline::get_cull_mode() const
	{
		return CullingMode;
	}
	PolygonFillMode Pipeline::get_fill_mode() const
	{
		return FillMode;
	}
	PrimitiveTopology Pipeline::get_primitives() const
	{
		return Primitives;
	}
	const ShaderSet* Pipeline::get_shader_set() const
	{
		return ShaderSet;
	}
	VertexLayoutDescription Pipeline::get_vertex_layout() const
	{
		return VertexLayout;
	}
	const Array<ResourceLayout*>& Pipeline::get_resource_layouts_fast() const
	{
		return ResourceLayouts;
	}
	Array<ResourceLayout*> Pipeline::get_resource_layouts_slow() const
	{
		return ResourceLayouts;
	}
}