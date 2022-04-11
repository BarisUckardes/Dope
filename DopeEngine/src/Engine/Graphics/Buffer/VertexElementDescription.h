#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Buffer/VertexElementDataType.h>

namespace DopeEngine
{
	/// <summary>
	/// Represents a single attribute of a vertex layout
	/// </summary>
	struct DOPE_ENGINE_API VertexElementDescription
	{

		VertexElementDescription(const String& name,
			const unsigned int componentCount, const unsigned int elementSizeInBytes,
			const bool normalized,
			const VertexElementDataType dataType) : Name(name), ComponentCount(componentCount), ElementSizeInBytes(elementSizeInBytes), Normalized(normalized), DataType(dataType)
		{}
		VertexElementDescription() = default;
		~VertexElementDescription() = default;

		/// <summary>
		/// Name of the attribute
		/// </summary>
		String Name;

		/// <summary>
		/// Component quantity
		/// </summary>
		unsigned int ComponentCount;

		/// <summary>
		/// Size of the each component
		/// </summary>
		unsigned int ElementSizeInBytes;

		/// <summary>
		/// Data is normalized or not
		/// </summary>
		bool Normalized;

		/// <summary>
		/// Attribute data type
		/// </summary>
		VertexElementDataType DataType;
	};
}