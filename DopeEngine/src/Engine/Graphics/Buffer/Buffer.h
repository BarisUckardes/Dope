#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Buffer/BufferType.h>

namespace DopeEngine
{
	/// <summary>
	/// Base buffer object for all buffers owned by a device
	/// </summary>
	class DOPE_ENGINE_API Buffer : public DeviceObject
	{
	public:
		Buffer(const BufferType type);
		~Buffer() = default;

		/// <summary>
		/// Returns the type of this buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE BufferType get_type() const;

		/// <summary>
		/// Returns the allocated size of this buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_allocated_size() const;
	protected:
		void set_allocated_size(const unsigned long size);
	private:
		BufferType Type;
		unsigned long AllocatedSize;
	};


}