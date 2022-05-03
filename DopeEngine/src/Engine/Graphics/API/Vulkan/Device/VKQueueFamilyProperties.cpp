#include "VKQueueFamilyProperties.h"
#include "VKQueueFamilyProperties.h"

namespace DopeEngine
{
   

    VkQueueFlags VKQueueFamilyProperties::get_flag() const
    {
        return Flag;
    }

    unsigned int VKQueueFamilyProperties::get_count() const
    {
        return Count;
    }

    unsigned int VKQueueFamilyProperties::get_family_index() const
    {
        return FamilyIndex;
    }



}