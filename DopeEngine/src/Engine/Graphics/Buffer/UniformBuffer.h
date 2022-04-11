#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic shader buffer resource abstraction class
	/// </summary>
	class DOPE_ENGINE_API UniformBuffer : public Buffer
	{
	public:
		UniformBuffer(const unsigned long allocatedSize);
		~UniformBuffer();
	};


}