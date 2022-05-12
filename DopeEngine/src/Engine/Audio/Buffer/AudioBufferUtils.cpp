#include "AudioBufferUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
    unsigned int AudioBufferUtils::get_channel_count(const AudioBufferFormat format)
    {
        switch (format)
        {
            case DopeEngine::AudioBufferFormat::Undefined:
                ASSERT(false, "AudioBufferUtils", "Undefined AudioBufferFormat!");
                break;
            case DopeEngine::AudioBufferFormat::Mono8Bit:
                return 1;
                break;
            case DopeEngine::AudioBufferFormat::Mono16Bit:
                return 1;
                break;
            case DopeEngine::AudioBufferFormat::Stereo8Bit:
                return 2;
                break;
            case DopeEngine::AudioBufferFormat::Stereo16Bit:
                return 2;
                break;
            default:
                ASSERT(false, "AudioBufferUtils", "Invalid AudioBufferFormat, cannot produce channel count");
                break;
        }
    }

    unsigned int AudioBufferUtils::get_sample_count(const AudioBufferFormat format)
    {
        switch (format)
        {
        case DopeEngine::AudioBufferFormat::Undefined:
            ASSERT(false,"AudioBufferUtils","Undefined AudioBufferFormat!")
            break;
        case DopeEngine::AudioBufferFormat::Mono8Bit:
            return 8;
            break;
        case DopeEngine::AudioBufferFormat::Mono16Bit:
            return 16;
            break;
        case DopeEngine::AudioBufferFormat::Stereo8Bit:
            return 8;
            break;
        case DopeEngine::AudioBufferFormat::Stereo16Bit:
            return 16;
            break;
        default:
            ASSERT(false, "AudioBufferUtils", "Invalid AudioBufferFormat, cannot produce sample count");
            break;
        }
    }

}