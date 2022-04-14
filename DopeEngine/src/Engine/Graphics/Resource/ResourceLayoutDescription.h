#pragma once
#include <Engine/Graphics/Resource/ResourceLayoutElementDescription.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	/// <summary>
	/// Description for creating a resource layout device object
	/// </summary>
	struct DOPE_ENGINE_API ResourceLayoutDescription
	{
		ResourceLayoutDescription(const Array<ResourceLayoutElementDescription>& elements) : Elements(elements) {}
		ResourceLayoutDescription() = default;
		~ResourceLayoutDescription() = default;

		/// <summary>
		/// Resource description elements
		/// </summary>
		Array<ResourceLayoutElementDescription> Elements;
	};
}