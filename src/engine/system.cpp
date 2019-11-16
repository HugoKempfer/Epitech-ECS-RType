/*
** EPITECH PROJECT, 2019
** system
** File description:
** Single responsability game logic unit
*/

#include <iostream>
#include <unordered_set>
#include "engine/system.hpp"

namespace Engine
{
	System::System(World &world, std::unordered_set<int64_t> componentAccess,
				std::unordered_set<int64_t> affectToState)
			: _world(world), writeComponentAccess(componentAccess), executeOnState(affectToState)
		{}

	void System::registerComponentStorage(int64_t uuid, std::vector<std::unique_ptr<Storable>> &storable)
	{
		_component.insert({uuid, storable});
	}

} /* Engine */
