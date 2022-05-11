#pragma once
#include <Engine/Audio/State/AudioListenerState.h>
#include <Engine/Audio/API/OpenAL/Core/OpenALCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenALListenerState : public AudioListenerState
	{
	public:
		OpenALListenerState(const AudioListenerStateDesc& desc);
		virtual ~OpenALListenerState() final override = default ;

	private:


	};


}