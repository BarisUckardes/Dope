#include "KeyboardKeyEvent.h"

namespace DopeEngine
{
    KeyboardKeyEvent::KeyboardKeyEvent(const unsigned int relatedKey)
    {
        RelatedKey = relatedKey;
    }
    unsigned int KeyboardKeyEvent::get_key() const
    {
        return RelatedKey;
    }
}