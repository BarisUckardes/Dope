#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/Buffer/BufferType.h>
#include <Engine/Graphics/Buffer/BufferDescription.h>
#include <Engine/Core/Definitions.h>

namespace DopeEngine
{
	/// <summary>
	/// Base buffer object for all buffers owned by a device
	/// </summary>
	class DOPE_ENGINE_API GraphicsBuffer : public GraphicsDeviceObject
	{
	public:
		GraphicsBuffer(const BufferDescription& descriptipn);
		virtual ~GraphicsBuffer() = default;

		/// <summary>
		/// Returns the type of this buffer
		/// </summary>
		/// <returns></returns>
		BufferType get_buffer_type() const;

		/// <summary>
		/// Returns the name of this buffer
		/// </summary>
		/// <returns></returns>
		String get_buffer_name() const;

		/// <summary>
		/// Returns the allocated size of this buffer
		/// </summary>
		/// <returns></returns>
		unsigned long get_allocated_size() const;

		/// <summary>
		/// Returns the element size
		/// </summary>
		/// <returns></returns>
		unsigned int get_item_size() const;
	private:
		BufferType Type;
		String Name;
		unsigned long AllocatedSize;
		unsigned int ItemSize;
	};


}