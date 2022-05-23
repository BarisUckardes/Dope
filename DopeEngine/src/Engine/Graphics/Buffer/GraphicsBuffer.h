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

		BufferType get_buffer_type() const;
		String get_buffer_name() const;
		unsigned long get_allocated_size() const;
		unsigned int get_item_size() const;

	private:
		BufferType Type;
		String Name;
		unsigned long AllocatedSize;
		unsigned int ItemSize;
	};


}