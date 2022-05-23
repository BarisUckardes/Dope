#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/RenderPass/BlendState.h>
#include <Engine/Graphics/RenderPass/DepthComparisionKind.h>
#include <Engine/Graphics/RenderPass/FronFaceMode.h>
#include <Engine/Graphics/RenderPass/FaceCullMode.h>
#include <Engine/Graphics/RenderPass/PolygonFillMode.h>
#include <Engine/Graphics/RenderPass/PrimitiveTopology.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
#include <Engine/Graphics/RenderPass/RenderPassType.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Resource/GraphicsResourceDesc.h>
#include <Engine/Graphics/Resource/GraphicsResourceSlotDesc.h>
#include <Engine/Graphics/RenderPass/ViewportDesc.h>
#include <Engine/Graphics/RenderPass/ScissorsDesc.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for creating a renderpass
	/// </summary>
	struct DOPE_ENGINE_API RenderPassDesc
	{
		RenderPassDesc() : BlendingState(BlendState::SingleOverride), DepthComparision(DepthComparisionKind::Always),DepthTest(false),DepthWrite(false),
		FrontFace(FrontFaceMode::CounterClockwise),CullFace(FaceCullMode::DontCull),FillMode(PolygonFillMode::Fill),DepthClip(false),ScissorTest(false),Primitives(PrimitiveTopology::Triangles),
		ShaderSet(Array<Shader*>()),LayoutDescription(VertexLayoutDescription()),TargetFramebuffer(nullptr),Type(RenderPassType::Graphics) {};
		~RenderPassDesc() = default;

		BlendState BlendingState;
		DepthComparisionKind DepthComparision;
		bool DepthTest;
		bool DepthWrite;
		FrontFaceMode FrontFace;
		FaceCullMode CullFace;
		PolygonFillMode FillMode;
		bool DepthClip;
		bool ScissorTest;
		PrimitiveTopology Primitives;
		Array<Shader*> ShaderSet;
		Framebuffer* TargetFramebuffer;
		VertexLayoutDescription LayoutDescription;
		Array<GraphicsResourceSlotDesc> ResourceSlots;
		RenderPassType Type;
	};
}