#include "OpenGLRenderPassUtils.h"
#include <GLAD/glad.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	DEPTH_FUNCTION OpenGLRenderPassUtils::get_depth_function(const DepthComparisionKind function)
	{
		switch (function)
		{
			case DepthComparisionKind::Never:
				return  GL_NEVER;
				break;
			case DepthComparisionKind::Less:
				return GL_LESS;
				break;
			case DepthComparisionKind::Equal:
				return GL_EQUAL;
				break;
			case DepthComparisionKind::LessEqual:
				return GL_LEQUAL;
				break;
			case DepthComparisionKind::Greater:
				return GL_GREATER;
				break;
			case DepthComparisionKind::NotEqual:
				return GL_NOTEQUAL;
				break;
			case DepthComparisionKind::GreaterOrEqual:
				return GL_GEQUAL;
				break;
			case DepthComparisionKind::Always:
				return GL_ALWAYS;
				break;
			default:
				ASSERT(false, "OpenGLPipelineUtils", "Invalid DepthComparisionKind");
				return GL_NONE;
				break;
		}
	}
	FRONT_FACE OpenGLRenderPassUtils::get_front_face(const FrontFaceMode frontFace)
	{
		switch (frontFace)
		{
			case DopeEngine::FrontFaceMode::Clockwise:
				return GL_CCW;
				break;
			case DopeEngine::FrontFaceMode::CounterClockwise:
				return GL_CW;
				break;
			default:
				ASSERT(false, "OpenGLPipelineUtils", "Invalid frontfacemode");
				return GL_NONE;
				break;
		}
	}
	CULL_MODE OpenGLRenderPassUtils::get_cull_mode(const FaceCullMode face)
	{
		switch (face)
		{
			case DopeEngine::FaceCullMode::Front:
				return GL_FRONT;
				break;
			case DopeEngine::FaceCullMode::Back:
				return GL_BACK;
				break;
			case DopeEngine::FaceCullMode::FrontAndBack:
				return GL_FRONT_AND_BACK;
				break;
			case DopeEngine::FaceCullMode::DontCull:
				return GL_NEVER;
				break;
			default:
				ASSERT(false, "OpenGLPipelineUtils", "Invalid cullmode");
				return GL_NONE;
				break;
		}
	}
	FILL_MODE OpenGLRenderPassUtils::get_fill_mode(const PolygonFillMode fillMode)
	{
		switch (fillMode)
		{
			case DopeEngine::PolygonFillMode::Point:
				return GL_POINT;
				break;
			case DopeEngine::PolygonFillMode::Line:
				return GL_LINE;
				break;
			case DopeEngine::PolygonFillMode::Fill:
				return GL_FILL;
				break;
			default:
				ASSERT(false, "OpenGLPipelineUtils", "Invalid polygonfillmode");
				return GL_NONE;
				break;
		}
	}
	PRIMITIVE OpenGLRenderPassUtils::get_primitive(const PrimitiveTopology primitive)
	{
		switch (primitive)
		{
			case DopeEngine::PrimitiveTopology::Points:
				return GL_POINTS;
				break;
			case DopeEngine::PrimitiveTopology::Lines:
				return GL_LINES;
				break;
			case DopeEngine::PrimitiveTopology::Triangles:
				return GL_TRIANGLES;
				break;
			case DopeEngine::PrimitiveTopology::Patches:
				return GL_PATCHES;
				break;
			default:
				ASSERT(false, "OpenGLPipelineUtils", "Invalid primitivetopology");
				return GL_NONE;
				break;
		}
	}
}