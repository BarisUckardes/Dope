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

		/// <summary>
		/// Returns the blending state for this pipeline
		/// </summary>
		/// <returns></returns>
		BlendState get_blending() const;

		/// <summary>
		/// Returns the depth function kind for this pipeline
		/// </summary>
		/// <returns></returns>
		DepthComparisionKind get_depth_function() const;

		/// <summary>
		/// Returns whether depth testing is enabled or not
		/// </summary>
		/// <returns></returns>
		bool is_depth_test_enabled() const;

		/// <summary>
		/// Returns whether depth writing is enabled or not
		/// </summary>
		/// <returns></returns>
		bool is_depth_write_enabled() const;

		/// <summary>
		/// Returns the front face render mode
		/// </summary>
		/// <returns></returns>
		FrontFaceMode get_front_face() const;

		/// <summary>
		/// Returns the culling face mode
		/// </summary>
		/// <returns></returns>
		FaceCullMode get_cull_mode() const;

		/// <summary>
		/// Returns the polygon fill mode
		/// </summary>
		/// <returns></returns>
		PolygonFillMode get_fill_mode() const;

		/// <summary>
		/// Returns the target primitives
		/// </summary>
		/// <returns></returns>
		PrimitiveTopology get_primitives() const;

		/// <summary>
		/// Returns the shader set
		/// </summary>
		/// <returns></returns>
		Array<Shader*> get_shader_set() const;

		/// <summary>
		/// Returns the layout of the vertex
		/// </summary>
		/// <returns></returns>
		VertexLayoutDescription get_vertex_layout() const;

		/// <summary>
		/// Returns the target framebuffer
		/// </summary>
		/// <returns></returns>
		Framebuffer* get_target_framebuffer() const;

		/// <summary>
		/// Returns a copy of the resource layouts
		/// </summary>
		/// <returns></returns>
		Array<GraphicsResourceSlotDesc> get_resource_slots() const;

		/// <summary>
		/// Returns the type of this pipeline
		/// </summary>
		/// <returns></returns>
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