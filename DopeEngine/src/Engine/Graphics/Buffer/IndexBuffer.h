#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Graphics/Buffer/IndexBufferDescription.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics API agnostic index buffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const IndexBufferDescription& description);
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Returns a copy of the description
		/// </summary>
		/// <returns></returns>
		FORCEINLINE IndexBufferDescription get_description() const;

		/// <summary>
		/// Returns the index count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_index_count() const;

		/// <summary>
		/// Allocates with the given index count
		/// </summary>
		/// <param name="count"></param>
		void allocate(unsigned long count);

		/// <summary>
		/// Updates the index buffer region with the given data
		/// </summary>
		/// <param name="data"></param>
		void update(const Byte* data);

	protected:
		virtual void allocate_impl(const unsigned long count) = 0;
		virtual void update_impl(const Byte* data) = 0;
	private:
		void calculate_diagnostics();
	private:
		IndexBufferDescription Description;
		unsigned long IndexCount;
	};


}