#include "UniformBuffer.h"

namespace DopeEngine
{
	UniformBuffer::UniformBuffer(const String& name,const unsigned long allocatedSize) : Buffer(BufferDescription(BufferType::UniformBuffer,name, allocatedSize))
	{

	}
}