#include "VertexLayoutDescription.h"
#include <Engine/Graphics/Vertex/VertexUtils.h>

namespace DopeEngine
{
	VertexLayoutDescription::VertexLayoutDescription(const Array<VertexElementDescription>& descriptions)
	{
		ElementDescriptions = descriptions;
		Stride = 0;
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
	unsigned int VertexLayoutDescription::get_stride() const
	{
		return Stride;
	}
	void VertexLayoutDescription::calculate_stride()
	{
		for (unsigned int i = 0; i < ElementDescriptions.get_cursor(); i++)
		{
			const VertexElementDescription& description = ElementDescriptions[i];
			Stride += VertexUtils::get_data_type_size(description.DataType);
		}
	}
}