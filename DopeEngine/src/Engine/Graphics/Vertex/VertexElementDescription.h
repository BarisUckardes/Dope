#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Vertex/VertexElementDataType.h>

namespace DopeEngine
{
	/// <summary>
	/// Represents a single attribute of a vertex layout
	/// </summary>
	struct DOPE_ENGINE_API VertexElementDescription
	{

		VertexElementDescription(const String& name, const VertexElementDataType dataType, const bool normalized) : Name(name), Normalized(normalized), DataType(dataType)
		{}
		VertexElementDescription() = default;
		~VertexElementDescription() = default;

		/// <summary>
		/// Name of the attribute
		/// </summary>
		String Name;

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