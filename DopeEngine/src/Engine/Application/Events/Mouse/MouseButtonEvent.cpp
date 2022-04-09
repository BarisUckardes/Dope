#include "MouseButtonEvent.h"

unsigned int DopeEngine::MouseButtonEvent::get_button() const
{
    return RelatedButton;
}

DopeEngine::MouseButtonEvent::MouseButtonEvent(const unsigned int relatedButton)
{
    RelatedButton = relatedButton;
}
