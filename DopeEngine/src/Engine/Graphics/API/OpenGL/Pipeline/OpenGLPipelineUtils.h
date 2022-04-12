#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLPipelineUtils
	{
	public:
		OpenGLPipelineUtils() = delete;
		~OpenGLPipelineUtils() = delete;

		FORCEINLINE static DEPTH_FUNCTION get_depth_function(const DepthComparisionKind function);
		FORCEINLINE static FRONT_FACE get_front_face(const FrontFaceMode frontFace);
		FORCEINLINE static CULL_MODE get_cull_mode(const FaceCullMode face);
		FORCEINLINE static FILL_MODE get_fill_mode(const PolygonFillMode fillMode);
		FORCEINLINE static PRIMITIVE get_primitive(const PrimitiveTopology primitive);
	};


}