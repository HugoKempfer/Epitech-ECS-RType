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
	System::System(World &world,
			std::unordered_set<int64_t> componentAccess,
			std::unordered_set<int64_t> ressourceAccess,
			std::unordered_set<int64_t> affectToState)
			: _world(world),
			writeComponentAccess(componentAccess),
			writeRessourceAccess(ressourceAccess),
			executeOnState(affectToState)
		{}

	void System::registerComponentStorage(int64_t uuid, std::vector<std::unique_ptr<Storable>> &storable)
	{
		_component.insert({uuid, storable});
	}

	void System::registerRessourceStorage(int64_t uuid, Storable &ressource)
	{
		_ressources.insert({uuid, ressource});
	}

} /* Engine */
