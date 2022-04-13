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
		BufferDescription(const BufferType type,const String& name,const unsigned long allocatedSize) : Type(type),Name(name), AllocatedSize(allocatedSize) {}
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
	};
}