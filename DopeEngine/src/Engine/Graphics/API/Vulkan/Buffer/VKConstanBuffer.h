#pragma once
#include <Engine/Graphics/Buffer/UniformBuffer.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKConstantBuffer : public UniformBuffer
	{
	public:
		VKConstantBuffer(const BufferDescription& desc, VKGraphicsDevice* device);
		virtual ~VKConstantBuffer() override;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkBuffer Buffer;
	};
}