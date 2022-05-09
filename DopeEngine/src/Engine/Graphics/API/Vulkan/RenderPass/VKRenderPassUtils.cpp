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

	VkShaderStageFlagBits VKRenderPassUtils::get_vk_shader_stage(const ShaderType shaderType)
	{
		switch (shaderType)
		{
			case DopeEngine::ShaderType::Vertex:
				return VK_SHADER_STAGE_VERTEX_BIT;
				break;
			case DopeEngine::ShaderType::Fragment:
				return VK_SHADER_STAGE_FRAGMENT_BIT;
				break;
			case DopeEngine::ShaderType::Geometry:
				return VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			case DopeEngine::ShaderType::TesellationEval:
				return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
				break;
			case DopeEngine::ShaderType::TesellationControl:
				return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
				break;
			case DopeEngine::ShaderType::Compute:
				return VK_SHADER_STAGE_COMPUTE_BIT;
				break;
			default:
				ASSERT(false, "VKPipelineUtils", "Invalid ShaderType, cannot produce VkShaderStageFlagBits");
				break;
		}
	}

}