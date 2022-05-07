#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/RenderPass/BlendState.h>
#include <Engine/Graphics/RenderPass/DepthComparisionKind.h>
#include <Engine/Graphics/RenderPass/FronFaceMode.h>
#include <Engine/Graphics/RenderPass/FaceCullMode.h>
#include <Engine/Graphics/RenderPass/PolygonFillMode.h>
#include <Engine/Graphics/RenderPass/PrimitiveTopology.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
#include <Engine/Graphics/Resource/ResourceLayout.h>
#include <Engine/Graphics/RenderPass/RenderPassType.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
namespace DopeEngine
{
	/// <summary>
	/// Description for creating a pipeline
	/// </summary>
	struct DOPE_ENGINE_API RenderPassDesc
	{
		RenderPassDesc(const BlendState blending,
			const DepthComparisionKind depthComparisionKind, const bool depthTest, const bool depthWrite,
			const FrontFaceMode fronFace, const FaceCullMode cullFace, const PolygonFillMode fillMode,
			const bool depthClip, const bool scissorTest,
			const PrimitiveTopology primitives,const Array<Shader*> shaders,const VertexLayoutDescription& layoutDescription,const Array<ResourceLayout*>& resourceLayouts,Framebuffer* targetFramebuffer,
			const RenderPassType type) : BlendingState(blending),
			DepthComparision(depthComparisionKind),DepthTest(depthTest),DepthWrite(depthWrite),
			FrontFace(fronFace),CullFace(cullFace),FillMode(fillMode),
			DepthClip(depthClip),ScissorTest(scissorTest),
			Primitives(primitives),ShaderSet(shaders),TargetFramebuffer(targetFramebuffer), LayoutDescription(layoutDescription), ResourceLayouts(resourceLayouts),
			Type(type)
		{}

		RenderPassDesc() : BlendingState(BlendState::SingleOverride), DepthComparision(DepthComparisionKind::Always),DepthTest(false),DepthWrite(false),
		FrontFace(FrontFaceMode::CounterClockwise),CullFace(FaceCullMode::DontCull),FillMode(PolygonFillMode::Fill),DepthClip(false),ScissorTest(false),Primitives(PrimitiveTopology::Triangles),
		ShaderSet(Array<Shader*>()),LayoutDescription(VertexLayoutDescription()),TargetFramebuffer(nullptr) {};
		~RenderPassDesc() = default;

		/// <summary>
		/// Blending function
		/// </summary>
		BlendState BlendingState;

		/// <summary>
		/// Depth comparision function
		/// </summary>
		DepthComparisionKind DepthComparision;

		/// <summary>
		/// Depth testing enabled or not
		/// </summary>
		bool DepthTest;

		/// <summary>
		/// Depth write enabled or not
		/// </summary>
		bool DepthWrite;

		/// <summary>
		/// Target front face
		/// </summary>
		FrontFaceMode FrontFace;

		/// <summary>
		/// Target cull face
		/// </summary>
		FaceCullMode CullFace;

		/// <summary>
		/// Fill method for the polygons
		/// </summary>
		PolygonFillMode FillMode;

		/// <summary>
		/// Depth clipping enabled or not
		/// </summary>
		bool DepthClip;

		/// <summary>
		/// Scissor test enabled or not
		/// </summary>
		bool ScissorTest;

		/// <summary>
		/// Target primitive types
		/// </summary>
		PrimitiveTopology Primitives;

		/// <summary>
		/// Target shader set
		/// </summary>
		Array<Shader*> ShaderSet;

		/// <summary>
		/// Target framebuffer
		/// </summary>
		Framebuffer* TargetFramebuffer;

		/// <summary>
		/// Vertex layout
		/// </summary>
		VertexLayoutDescription LayoutDescription;

		/// <summary>
		/// Resource layouts
		/// </summary>
		Array<ResourceLayout*> ResourceLayouts;

		/// <summary>
		/// Type of the render pass
		/// </summary>
		RenderPassType Type;
	};
}