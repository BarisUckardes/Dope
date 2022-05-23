#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/RenderPass/RenderPassDesc.h>
#include <Engine/Graphics/RenderPass/RenderPassType.h>
#include <Engine/Graphics/Resource/GraphicsResourceSlotDesc.h>
namespace DopeEngine
{
	class Shader;
	/// <summary>
	/// Graphics api agnostic render pass abstraction class
	/// </summary>
	class DOPE_ENGINE_API RenderPass : public GraphicsDeviceObject
	{
	public:
		RenderPass(const RenderPassDesc& description);
		virtual ~RenderPass() = 0 {}

		BlendState get_blending() const;
		DepthComparisionKind get_depth_function() const;
		bool is_depth_test_enabled() const;
		bool is_depth_write_enabled() const;
		FrontFaceMode get_front_face() const;
		FaceCullMode get_cull_mode() const;
		PolygonFillMode get_fill_mode() const;
		PrimitiveTopology get_primitives() const;
		Array<Shader*> get_shader_set() const;
		VertexLayoutDescription get_vertex_layout() const;
		Framebuffer* get_target_framebuffer() const;
		Array<GraphicsResourceSlotDesc> get_resource_slots() const;
		RenderPassType get_type() const;
	private:
		BlendState Blending;
		DepthComparisionKind DepthFunction;
		bool DepthTest;
		bool DepthWrite;
		FrontFaceMode FrontFace;
		FaceCullMode CullingMode;
		PolygonFillMode FillMode;
		PrimitiveTopology Primitives;
		Array<Shader*> Shaders;
		Framebuffer* TargetFramebuffer;
		VertexLayoutDescription VertexLayout;
		Array<GraphicsResourceSlotDesc> ResourceSlots;
		RenderPassType Type;
	};


}