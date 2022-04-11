#include "VertexLayoutDescription.h"

namespace DopeEngine
{
	VertexLayoutDescription::VertexLayoutDescription(const Array<VertexElementDescription>& descriptions)
	{
		/*
		* Initialize
		*/
		ElementDescriptions = descriptions;
		Stride = 0;

		/*
		* Calculate stride of this layout
		*/
		calculate_stride();
	}
	VertexLayoutDescription::VertexLayoutDescription()
	{
		Stride = 0;
	}
	const Array<VertexElementDescription>& VertexLayoutDescription::get_elements_fast() const
	{
		return ElementDescriptions;
	}
	Array<VertexElementDescription> VertexLayoutDescription::get_elements_slow() const
	{
		return ElementDescriptions;
	}
	unsigned int VertexLayoutDescription::get_stride() const
	{
		return Stride;
	}
	void VertexLayoutDescription::calculate_stride()
	{
		for (unsigned int i = 0; i < ElementDescriptions.get_cursor(); i++)
		{
			const VertexElementDescription& description = ElementDescriptions[i];
			Stride += description.ComponentCount * description.ElementSizeInBytes;
		}
	}
}