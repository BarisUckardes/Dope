#pragma once
#include <OPENAL/al.h>
#include <OPENAL/alc.h>

void validate_openal_error();
#define VALIDATE_OPENAL_ERROR() validate_openal_error();

typedef unsigned int BUFFER_HANDLE;
typedef unsigned int SOURCE_STATE_HANDLE;
