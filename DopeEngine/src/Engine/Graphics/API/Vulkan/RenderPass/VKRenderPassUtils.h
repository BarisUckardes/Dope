#pragma once
#include <Engine/Graphics/RenderPass/RenderPassDesc.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKRenderPassUtils
	{
	public:
		VKRenderPassUtils() = delete;
		~VKRenderPassUtils() = delete;

		FORCEINLINE static VkPrimitiveTopology get_vk_primitive_topology(const PrimitiveTopology primitives);
		FORCEINLINE static VkCullModeFlags get_vk_cull_mode(const FaceCullMode cullMode);
		FORCEINLINE static VkFrontFace get_vk_front_face(const FrontFaceMode frontFace);
		FORCEINLINE static VkPolygonMode get_vk_polygon_mode(const PolygonFillMode polygonFillMode);
		FORCEINLINE static VkShaderStageFlagBits get_vk_shader_stage(const ShaderType shaderType);
	};


}