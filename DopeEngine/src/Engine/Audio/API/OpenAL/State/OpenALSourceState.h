#pragma once
#include <Engine/Audio/State/AudioSourceState.h>
#include <Engine/Audio/API/OpenAL/Core/OpenALCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenALSourceState : public AudioSourceState
	{
	public:
		OpenALSourceState(const AudioSourceStateDesc& desc);
		virtual ~OpenALSourceState() final override ;

		FORCEINLINE SOURCE_STATE_HANDLE get_al_state_handle() const;
	private:
		SOURCE_STATE_HANDLE Handle;
	};


}