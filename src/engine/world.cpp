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
#include "engine/storable.hpp"
#include "engine/system.hpp"

namespace Engine {
	World::World()
		: _entities(*this)
	{}

	World &World::registerSystem(std::unique_ptr<System> &sys)
	{
		for (auto storage_id : sys->writeComponentAccess) {
			if (!_components.contains(storage_id)) {
				_components.insert({storage_id, std::vector<std::unique_ptr<Storable>>()});
			}
			sys->registerComponentStorage(storage_id, _components[storage_id]);
		}
		_systems.push_back(std::move(sys));
		return *this;
	}

	void World::registerRessource()
	{
		std::cerr << "Unimplemented" << std::endl;
	}

	Entity &World::createEntity()
	{
		return _entities.add();
	}

	Entity &World::getEntity(int64_t id)
	{
		return _entities[id];
	}

	void World::storeComponent(std::unique_ptr<Storable> &component)
	{
		if (!_components.contains(component->UUID)) {
			_components.insert({component->UUID, std::vector<std::unique_ptr<Storable>>()});
		}
		try {
			auto &storage = _components.at(component->UUID);
			storage.push_back(std::move(component));
		} catch(std::out_of_range e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void World::run()
	{
		while (!_states.empty()) {
			_states.current().onUpdate();
			for (auto &sys : _systems) {
				sys->run();
			}
		}
	}
}
