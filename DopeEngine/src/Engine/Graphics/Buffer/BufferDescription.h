#pragma once
#include <Engine/Graphics/Buffer/BufferType.h>

namespace DopeEngine
{
	/// <summary>
	/// Used for creating a buffer
	/// </summary>
	struct DOPE_ENGINE_API BufferDescription
	{
		BufferDescription(const BufferType type,const unsigned long allocatedSize) : Type(type),AllocatedSize(allocatedSize) {}
		BufferDescription() = default;
		~BufferDescription() = default;

		/// <summary>
		/// The type of the buffer
		/// </summary>
		BufferType Type;

		/// <summary>
		/// Staticly allocated size of the buffer
		/// </summary>
		unsigned long AllocatedSize;
	};
}