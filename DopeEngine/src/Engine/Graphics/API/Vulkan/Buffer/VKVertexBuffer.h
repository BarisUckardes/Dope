#pragma once
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKVertexBuffer : public VertexBuffer
	{
	public:
		VKVertexBuffer(const BufferDescription& desc, VKGraphicsDevice* device);
		virtual ~VKVertexBuffer() override;

		FORCEINLINE VkBuffer get_vk_vertex_buffer() const;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkBuffer Buffer;
	};


}