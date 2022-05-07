#include "RenderPass.h"

namespace DopeEngine
{
	RenderPass::RenderPass(const RenderPassDesc& description) : DeviceObject(DeviceObjectType::RenderPass)
	{
		Blending = description.BlendingState;
		DepthFunction = description.DepthComparision;
		DepthTest = description.DepthTest;
		DepthWrite = description.DepthWrite;
		FrontFace = description.FrontFace;
		CullingMode = description.CullFace;
		FillMode = description.FillMode;
		Primitives = description.Primitives;
		Shaders = description.ShaderSet;
		VertexLayout = description.LayoutDescription;
		ResourceLayouts = description.ResourceLayouts;
		TargetFramebuffer = description.TargetFramebuffer;
	}
	BlendState RenderPass::get_blending() const
	{
		return Blending;
	}
	DepthComparisionKind RenderPass::get_depth_function() const
	{
		return DepthFunction;
	}
	bool RenderPass::is_depth_test_enabled() const
	{
		return DepthTest;
	}
	bool RenderPass::is_depth_write_enabled() const
	{
		return DepthWrite;
	}
	FrontFaceMode RenderPass::get_front_face() const
	{
		return FrontFace;
	}
	FaceCullMode RenderPass::get_cull_mode() const
	{
		return CullingMode;
	}
	PolygonFillMode RenderPass::get_fill_mode() const
	{
		return FillMode;
	}
	PrimitiveTopology RenderPass::get_primitives() const
	{
		return Primitives;
	}
	Array<Shader*> RenderPass::get_shader_set() const
	{
		return Shaders;
	}
	VertexLayoutDescription RenderPass::get_vertex_layout() const
	{
		return VertexLayout;
	}
	const Array<ResourceLayout*>& RenderPass::get_resource_layouts_fast() const
	{
		return ResourceLayouts;
	}
	Framebuffer* RenderPass::get_target_framebuffer() const
	{
		return TargetFramebuffer;
	}
	Array<ResourceLayout*> RenderPass::get_resource_layouts_slow() const
	{
		return ResourceLayouts;
	}
	RenderPassType RenderPass::get_type() const
	{
		return Type;
	}
}