/*
** EPITECH PROJECT, 2019
** world
** File description:
** Engine base container
*/

#include <unordered_map>
#include <vector>
#include "engine/world.hpp"
#include "engine/game_storage.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"

namespace Engine {
	World::World(int initialState)
		: _entities(*this)
	{
		/* TODO: push init state */
	}

	void World::registerSystem()
	{}

	void World::registerRessource()
	{}

	Entity &World::createEntity()
	{
		return _entities.add();
	}

	void World::run()
	{}

	void World::storeComponent(Component &component)
	{
		if (!_components.contains(component.componentTypeUUID)) {
			_components.insert({component.componentTypeUUID, std::vector<Component>()});
		}
		try {
			auto storage = _components.at(component.componentTypeUUID);
			storage.push_back(component);
		} catch(std::out_of_range e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
