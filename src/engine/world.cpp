/*
** EPITECH PROJECT, 2019
** world
** File description:
** Engine base container
*/

#include <unordered_map>
#include <vector>
#include "engine/game_storage.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "engine/storable.hpp"
#include "engine/world.hpp"
#include "engine/system.hpp"
#include "engine/state.hpp"

namespace Engine {
	World::World()
		: entities(*this)
	{}

	World::~World() {}

	World &World::registerSystem(std::unique_ptr<System> &sys)
	{
		for (auto storage_id : sys->writeComponentAccess) {
			if (!_components.contains(storage_id)) {
				_components.insert({storage_id, std::vector<std::unique_ptr<Storable>>()});
			}
			sys->registerComponentStorage(storage_id, _components[storage_id]);
		}
		_dispatcher._systems.push_back(std::move(sys));
		return *this;
	}

	void World::registerRessource()
	{
		std::cerr << "Unimplemented" << std::endl;
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
		while (!states.empty()) {
			states.current().onUpdate();
			for (auto &sys : _dispatcher._systems) {
				sys->run();
			}
			this->entities.processRemoval();
		}
		this->entities.removeAll();
		this->entities.processRemoval();
	}
}
