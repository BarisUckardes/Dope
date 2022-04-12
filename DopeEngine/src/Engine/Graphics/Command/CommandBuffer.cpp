#include "CommandBuffer.h"

namespace DopeEngine
{
	void CommandBuffer::lock()
	{
		/*
		* Clear cached state
		*/
		clear_cached_state();

		/*
		* Call impl
		*/
		lock_impl();
	}
	void CommandBuffer::unlock()
	{
		/*
		* Call impl
		*/
		unlock_impl();
	}
	void CommandBuffer::clear_cached_state()
	{
		CurrentBoundTextures = 0;
	}
}