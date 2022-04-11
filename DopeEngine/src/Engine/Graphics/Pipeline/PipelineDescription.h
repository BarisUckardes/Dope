#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Pipeline/BlendState.h>
#include <Engine/Graphics/Pipeline/DepthComparisionKind.h>
#include <Engine/Graphics/Pipeline/FronFaceMode.h>
#include <Engine/Graphics/Pipeline/FaceCullMode.h>
#include <Engine/Graphics/Pipeline/PolygonFillMode.h>
#include <Engine/Graphics/Pipeline/PrimitiveTopology.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API PipelineDescription
	{
		PipelineDescription(const BlendState blending,
			const DepthComparisionKind depthComparisionKind, const bool depthTest, const bool depthWrite,
			const FrontFaceMode fronFace, const FaceCullMode cullFace, const PolygonFillMode fillMode,
			const bool depthClip, const bool scissorTest,
			const PrimitiveTopology primitives) : BlendingState(blending),
			DepthComparision(depthComparisionKind),DepthTest(depthTest),DepthWrite(depthWrite),
			FrontFace(fronFace),CullFace(cullFace),FillMode(fillMode),
			DepthClip(depthClip),ScissorTest(scissorTest),
			Primitives(primitives) {}

		PipelineDescription() = default;
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
	};
}