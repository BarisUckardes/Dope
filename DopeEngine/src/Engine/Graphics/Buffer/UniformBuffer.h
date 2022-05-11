#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Buffer/GraphicsBuffer.h>
#include <Engine/Core/Definitions.h>
#include <Engine/Graphics/Buffer/BufferDescription.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic shader buffer resource abstraction class
	/// </summary>
	class DOPE_ENGINE_API UniformBuffer : public GraphicsBuffer
	{
	public:
		UniformBuffer(const BufferDescription& desc);
		virtual ~UniformBuffer() = default;
	};


}