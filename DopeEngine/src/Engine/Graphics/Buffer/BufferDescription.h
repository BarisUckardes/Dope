#pragma once
#include <Engine/Graphics/Buffer/BufferType.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Used for creating a buffer
	/// </summary>
	struct DOPE_ENGINE_API BufferDescription
	{
		BufferDescription(const String& name, const BufferType type,const unsigned long allocatedSize,unsigned int perItemSize) : Type(type),Name(name), AllocatedSize(allocatedSize),PerItemSize(perItemSize) {}
		BufferDescription() : Type(BufferType::VertexBuffer),Name("Undefined buffer"),AllocatedSize(0),PerItemSize(0) {}
		~BufferDescription() = default;

		BufferType Type;
		String Name;
		unsigned long AllocatedSize;
		unsigned int PerItemSize;
	};
}