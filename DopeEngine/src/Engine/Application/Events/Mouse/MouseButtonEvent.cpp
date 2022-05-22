#include "MouseButtonEvent.h"

namespace DopeEngine
{
    unsigned int MouseButtonEvent::get_button() const
    {
        return RelatedButton;
    }

    MouseButtonEvent::MouseButtonEvent(const unsigned int relatedButton)
    {
        RelatedButton = relatedButton;
    }

}