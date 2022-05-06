#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Pipeline/BlendState.h>
#include <Engine/Graphics/Pipeline/DepthComparisionKind.h>
#include <Engine/Graphics/Pipeline/FronFaceMode.h>
#include <Engine/Graphics/Pipeline/FaceCullMode.h>
#include <Engine/Graphics/Pipeline/PolygonFillMode.h>
#include <Engine/Graphics/Pipeline/PrimitiveTopology.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
#include <Engine/Graphics/Resource/ResourceLayout.h>
#include <Engine/Graphics/Pipeline/OutputDescription.h>
#include <Engine/Graphics/Pipeline/PipelineType.h>
#include <Engine/Graphics/Shader/Shader.h>
namespace DopeEngine
{
	/// <summary>
	/// Description for creating a pipeline
	/// </summary>
	struct DOPE_ENGINE_API PipelineDescription
	{
		PipelineDescription(const BlendState blending,
			const DepthComparisionKind depthComparisionKind, const bool depthTest, const bool depthWrite,
			const FrontFaceMode fronFace, const FaceCullMode cullFace, const PolygonFillMode fillMode,
			const bool depthClip, const bool scissorTest,
			const PrimitiveTopology primitives,const Array<Shader*> shaders,const VertexLayoutDescription& layoutDescription,const Array<ResourceLayout*>& resourceLayouts,const OutputDescription& outputDesc,
			const PipelineType type) : BlendingState(blending),
			DepthComparision(depthComparisionKind),DepthTest(depthTest),DepthWrite(depthWrite),
			FrontFace(fronFace),CullFace(cullFace),FillMode(fillMode),
			DepthClip(depthClip),ScissorTest(scissorTest),
			Primitives(primitives),ShaderSet(shaders),LayoutDescription(layoutDescription),ResourceLayouts(resourceLayouts),OutputDesc(outputDesc),
			Type(type)
		{}

		PipelineDescription() : BlendingState(BlendState::SingleOverride), DepthComparision(DepthComparisionKind::Always),DepthTest(false),DepthWrite(false),
		FrontFace(FrontFaceMode::CounterClockwise),CullFace(FaceCullMode::DontCull),FillMode(PolygonFillMode::Fill),DepthClip(false),ScissorTest(false),Primitives(PrimitiveTopology::Triangles),
		ShaderSet(Array<Shader*>()),OutputDesc(0,0,0,0,Array<TextureFormat>(),false),LayoutDescription(VertexLayoutDescription()) {};
		~PipelineDescription() = default;

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
		/// The output framebuffer description
		/// </summary>
		OutputDescription OutputDesc;

		/// <summary>
		/// Vertex layout
		/// </summary>
		VertexLayoutDescription LayoutDescription;

		/// <summary>
		/// Resource layouts
		/// </summary>
		Array<ResourceLayout*> ResourceLayouts;

		/// <summary>
		/// Type of the pipeline
		/// </summary>
		PipelineType Type;
	};
}