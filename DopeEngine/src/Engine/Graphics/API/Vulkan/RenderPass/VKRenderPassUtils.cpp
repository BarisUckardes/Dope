#include "VKRenderPassUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	VkPrimitiveTopology VKRenderPassUtils::get_vk_primitive_topology(const PrimitiveTopology primitives)
	{
		switch (primitives)
		{
			case DopeEngine::PrimitiveTopology::Points:
				return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				break;
			case DopeEngine::PrimitiveTopology::Lines:
				return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				break;
			case DopeEngine::PrimitiveTopology::Triangles:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				break;
			case DopeEngine::PrimitiveTopology::Patches:
				return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
				break;
			default:
				ASSERT(false, "VKPipelineUtils", "Invalid PrimitiveTopology, cannot produce VkPrimitiveTopology");
				break;
		}
	}

	VkCullModeFlags VKRenderPassUtils::get_vk_cull_mode(const FaceCullMode cullMode)
	{
		switch (cullMode)
		{
		case DopeEngine::FaceCullMode::Front:
			return VK_CULL_MODE_FRONT_BIT;
			break;
		case DopeEngine::FaceCullMode::Back:
			return VK_CULL_MODE_BACK_BIT;
			break;
		case DopeEngine::FaceCullMode::FrontAndBack:
			return VK_CULL_MODE_FRONT_AND_BACK;
			break;
		case DopeEngine::FaceCullMode::DontCull:
			return VK_CULL_MODE_NONE;
			break;
		default:
			ASSERT(false, "VKPipelineUtils", "Invalid FaceCullMode, cannot produce VkCullModeFlags");
			break;
		}
	}

	VkFrontFace VKRenderPassUtils::get_vk_front_face(const FrontFaceMode frontFace)
	{
		switch (frontFace)
		{
			case DopeEngine::FrontFaceMode::Clockwise:
				return VK_FRONT_FACE_CLOCKWISE;
				break;
			case DopeEngine::FrontFaceMode::CounterClockwise:
				return VK_FRONT_FACE_COUNTER_CLOCKWISE;
				break;
			default:
				ASSERT(false, "VKPipelineUtils", "Invalid FronFaceMode, cannot produce VkFrontFace");
				break;
		}
	}

	VkPolygonMode VKRenderPassUtils::get_vk_polygon_mode(const PolygonFillMode polygonFillMode)
	{
		switch (polygonFillMode)
		{
			case DopeEngine::PolygonFillMode::Point:
				return VK_POLYGON_MODE_POINT;
				break;
			case DopeEngine::PolygonFillMode::Line:
				return VK_POLYGON_MODE_LINE;
				break;
			case DopeEngine::PolygonFillMode::Fill:
				return VK_POLYGON_MODE_FILL;
				break;
			default:
				ASSERT(false, "VKPipelineUtils", "Invalid PolygonFillMode, cannot produce VkPolygonMode");
				break;
		}
	}

	VkShaderStageFlagBits VKRenderPassUtils::get_vk_shader_stage(const ShaderStage ShaderStage)
	{
		switch (ShaderStage)
		{
			case DopeEngine::ShaderStage::Vertex:
				return VK_SHADER_STAGE_VERTEX_BIT;
				break;
			case DopeEngine::ShaderStage::Fragment:
				return VK_SHADER_STAGE_FRAGMENT_BIT;
				break;
			case DopeEngine::ShaderStage::Geometry:
				return VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
				break;
			case DopeEngine::ShaderStage::Compute:
				return VK_SHADER_STAGE_COMPUTE_BIT;
				break;
			default:
				ASSERT(false, "VKPipelineUtils", "Invalid ShaderStage, cannot produce VkShaderStageFlagBits");
				break;
		}
	}

	VkPipelineBindPoint VKRenderPassUtils::get_vk_pipeline_type(const RenderPassType renderPassType)
	{
		switch (renderPassType)
		{
			case DopeEngine::RenderPassType::Graphics:
				return VK_PIPELINE_BIND_POINT_GRAPHICS;
				break;
			case DopeEngine::RenderPassType::Compute:
				break;
				return VK_PIPELINE_BIND_POINT_COMPUTE;
			default:
				ASSERT(false,"VkRenderPassUtils", "Invalid RenderPassType, cannot produce VkPipelineBindPoint!");
				break;
		}
	}

}