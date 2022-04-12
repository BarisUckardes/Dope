#include "Pipeline.h"

namespace DopeEngine
{
	Pipeline::Pipeline(const PipelineDescription& description)
	{
		Blending = description.BlendingState;
		DepthFunction = description.DepthComparision;
		DepthTest = description.DepthTest;
		DepthWrite = description.DepthWrite;
		FrontFace = description.FrontFace;
		CullingMode = description.CullFace;
		FillMode = description.FillMode;
		Primitives = description.Primitives;
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
}