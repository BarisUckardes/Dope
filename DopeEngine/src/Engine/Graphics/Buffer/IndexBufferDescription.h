#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for index buffer data layout
	/// </summary>
	struct DOPE_ENGINE_API IndexBufferDescription
	{
		IndexBufferDescription(const unsigned long long range,const unsigned int padding) : Range(range),Padding(padding) {}
		IndexBufferDescription() : Range(0),Padding(9) {}
		~IndexBufferDescription() = default;

		/// <summary>
		/// The interval which index index buffer element can cover
		/// </summary>
		unsigned long long Range;

		/// <summary>
		/// Byte size of this index buffer element
		/// </summary>
		unsigned int Padding;
	};
}