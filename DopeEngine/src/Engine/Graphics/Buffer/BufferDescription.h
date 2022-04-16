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
		BufferDescription() = default;
		~BufferDescription() = default;

		/// <summary>
		/// The type of the buffer
		/// </summary>
		BufferType Type;

		/// <summary>
		/// The name of the buffer
		/// </summary>
		String Name;

		/// <summary>
		/// Staticly allocated size of the buffer
		/// </summary>
		unsigned long AllocatedSize;

		/// <summary>
		/// Size of a single item
		/// </summary>
		unsigned int PerItemSize;
	};
}