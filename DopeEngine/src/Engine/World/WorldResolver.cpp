#include "WorldResolver.h"

namespace DopeEngine
{
	World* WorldResolver::get_owner_world() const
	{
		return OwnerWorld;
	}
	void WorldResolver::_set_owner_world(World* world)
	{
		OwnerWorld = world;
	}
}