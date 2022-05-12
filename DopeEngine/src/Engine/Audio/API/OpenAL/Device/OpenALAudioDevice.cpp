#include "OpenALAudioDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Audio/API/OpenAL/Device/OpenALAudioDeviceObjects.h>
#include <Engine/Audio/API/OpenAL/Buffer/OpenALBufferFormatUtils.h>

namespace DopeEngine
{
    OpenALAudioDevice::OpenALAudioDevice() : AudioDevice(AudioAPIType::OpenAL)
    {
        create();
    }

    OpenALAudioDevice::~OpenALAudioDevice()
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(Context);
        alcCloseDevice(Device);
    }
    void OpenALAudioDevice::create()
    {
       /*
       * Get default device
       */
       const ALCchar* defaultDeviceName = alcGetString(NULL,ALC_DEFAULT_DEVICE_SPECIFIER);
       Device = alcOpenDevice(defaultDeviceName);

       /*
       * Validate device creation
       */
       ASSERT(Device, "OpenALAudioDevice", "Device cannot be created!");

       /*
       * Create context
       */
       Context = alcCreateContext(Device, nullptr);

       /*
       * Validate context creation
       */
       ASSERT(Context, "OpenALAudioDevice", "Context cannot be created!");

       /*
       * Make context current
       */
       ASSERT(alcMakeContextCurrent(Context), "OpenALAudioDevice", "Context cannot be set as Current");
    }

    void OpenALAudioDevice::submit_listener_impl(const AudioListenerState* state)
    {
        /*
        * Get listener state
        */
        const Vector3f position = state->get_position();
        const Vector3f velocity = state->get_velocity();
        const float orientation = state->get_orientation();

        /*
        * Set listener state
        */
        alListener3f(AL_POSITION, position.X, position.Y, position.Z);
        alListener3f(AL_VELOCITY, velocity.X, velocity.Y, velocity.Z);
        alListeneri(AL_ORIENTATION, orientation);
    }

    void OpenALAudioDevice::submit_source_impl(const AudioSourceState* state, const AudioBuffer* buffer)
    {
        /*
        * Get al state and al buffer
        */
        const OpenALSourceState* alState = (const OpenALSourceState*)state;
        const OpenALBuffer* alBuffer = (const OpenALBuffer*)buffer;

        /*
        * Set source buffer
        */
        alSourcei(alState->get_al_state_handle(), AL_BUFFER, alBuffer->get_al_buffer_handle());
    }

    void OpenALAudioDevice::submit_play_source_impl(const AudioSourceState* state)
    {
        /*
        * Get al state
        */
        const OpenALSourceState* alState = (const OpenALSourceState*)state;

        /*
        * Play
        */
        alSourcePlay(alState->get_al_state_handle());
    }

    AudioBuffer* OpenALAudioDevice::create_buffer_impl(const AudioBufferDesc& desc)
    {
        return new OpenALBuffer(desc);
    }

    AudioSourceState* OpenALAudioDevice::create_source_state_impl(const AudioSourceStateDesc& desc)
    {

        return new OpenALSourceState(desc);
    }

    AudioListenerState* OpenALAudioDevice::create_listener_state_impl(const AudioListenerStateDesc& desc)
    {
        return new OpenALListenerState(desc);
    }

    void OpenALAudioDevice::update_buffer_impl(const Byte* data, AudioBuffer* buffer)
    {
        /*
        * Get as al buffer
        */
        const OpenALBuffer* alBuffer = (const OpenALBuffer*)buffer;

        /*
        * Set buffer data
        */
        alBufferData(alBuffer->get_al_buffer_handle(),OpenALBufferFormatUtils::get_al_buffer_format(alBuffer->get_format()),data,alBuffer->get_allocated_size(),alBuffer->get_frequency());
    }

    void OpenALAudioDevice::update_source_state_impl(const AudioSourceStateDesc& desc, AudioSourceState* state)
    {
        /*
        * Get as al buffer
        */
        const OpenALSourceState* alState = (const OpenALSourceState*)state;
        const SOURCE_STATE_HANDLE handle = alState->get_al_state_handle();
        const Vector3f position = alState->get_position();
        const Vector3f velocity = alState->get_velocity();

        /*
        * Set state
        */
        alSourcef(handle, AL_PITCH, alState->get_pitch());
        alSourcef(handle, AL_GAIN, alState->get_gain());
        alSource3f(handle, AL_POSITION, position.X, position.Y, position.Z);
        alSource3f(handle, AL_VELOCITY, velocity.X, velocity.Y, velocity.Z);
        alSourcei(handle, AL_LOOPING, alState->is_looping() ? AL_TRUE : AL_FALSE);

    }

    void OpenALAudioDevice::update_listener_state_impl(const AudioListenerStateDesc& desc, AudioListenerState* state)
    {

    }

}