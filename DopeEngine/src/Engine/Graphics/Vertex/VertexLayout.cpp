#include "VertexLayout.h"

namespace DopeEngine
{
	VertexLayout::VertexLayout(const VertexLayoutDescription& description)
	{
		Description = description;
	}
	const VertexLayoutDescription& VertexLayout::get_description_fast() const
	{
		return Description;
	}
	VertexLayoutDescription VertexLayout::get_description_slow() const
	{
		return Description;
	}
}