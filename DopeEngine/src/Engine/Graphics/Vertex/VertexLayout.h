#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>

namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic vertex layout abstraction class
	/// </summary>
	class DOPE_ENGINE_API VertexLayout : public DeviceObject
	{
	public:
		VertexLayout(const VertexLayoutDescription& description);
		virtual ~VertexLayout() = default;

		/// <summary>
		/// Returns a reference to the description
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const VertexLayoutDescription& get_description_fast() const;

		/// <summary>
		/// Returns a copy of the description
		/// </summary>
		/// <returns></returns>
		FORCEINLINE VertexLayoutDescription get_description_slow() const;

		/// <summary>
		/// Creates the layout object
		/// </summary>
		virtual void create_layout() = 0;

		/// <summary>
		/// Sets the layout active
		/// </summary>
		virtual void set_layout_active() const = 0;
	private:
		VertexLayoutDescription Description;
	};


}