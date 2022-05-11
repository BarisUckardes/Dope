#include "OpenALCore.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{

}

void validate_openal_error()
{
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
		return;

	switch (error)
	{
	case AL_INVALID_NAME:
		LOG("OpenAL", "Error: invalid ID passed to an OpenALFunction");
		break;
	}
}
