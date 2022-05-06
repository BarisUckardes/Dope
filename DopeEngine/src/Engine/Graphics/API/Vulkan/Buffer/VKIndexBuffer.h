#pragma once
#include <Engine/Graphics/Buffer/IndexBuffer.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKIndexBuffer : public IndexBuffer
	{
	public:
		VKIndexBuffer(const BufferDescription& desc, VKGraphicsDevice* device);
		virtual ~VKIndexBuffer() override;

	private:
		void create(VKGraphicsDevice* device);
	private:
		VkBuffer Buffer;
	};


}