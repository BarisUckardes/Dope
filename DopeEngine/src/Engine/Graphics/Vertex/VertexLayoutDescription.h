#pragma once
#include <Engine/Graphics/Vertex/VertexElementDescription.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API VertexLayoutDescription
	{
	public:
		VertexLayoutDescription(const Array<VertexElementDescription>& descriptions);
		VertexLayoutDescription();
		~VertexLayoutDescription() = default;

		FORCEINLINE const Array<VertexElementDescription>& get_elements_fast() const;
		FORCEINLINE unsigned int get_stride() const;
	private:
		void calculate_stride();
	private:
		Array<VertexElementDescription> ElementDescriptions;
		unsigned int Stride;
	};


}