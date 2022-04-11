#pragma once
#include <Engine/Graphics/Vertex/VertexElementDescription.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VertexLayoutDescription
	{
	public:
		VertexLayoutDescription(const Array<VertexElementDescription>& descriptions);
		VertexLayoutDescription();
		~VertexLayoutDescription() = default;

		/// <summary>
		/// Returns a reference to the elements list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<VertexElementDescription>& get_elements_fast() const;

		/// <summary>
		/// Returns a copy of the elements list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<VertexElementDescription> get_elements_slow() const;

		/// <summary>
		/// Returns the stride for this layout
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_stride() const;
	private:
		void calculate_stride();
	private:
		Array<VertexElementDescription> ElementDescriptions;
		unsigned int Stride;
	};


}