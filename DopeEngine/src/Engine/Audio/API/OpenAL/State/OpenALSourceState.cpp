#include "OpenALSourceState.h"

namespace DopeEngine
{
	OpenALSourceState::OpenALSourceState(const AudioSourceStateDesc& desc) : AudioSourceState(desc)
	{
		/*
		* Gen source state
		*/
		alGenSources(1, &Handle);
	}

	OpenALSourceState::~OpenALSourceState()
	{
		alDeleteSources(1, &Handle);
	}

	SOURCE_STATE_HANDLE OpenALSourceState::get_al_state_handle() const
	{
		return Handle;
	}

}