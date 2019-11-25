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
		: entities(*this, _components), eventsCtx(*this)	{}

	World::~World() {}

	void World::processSystemRegistration(std::unique_ptr<System> &sys)
	{
		std::cerr << "REGISTER SYSTEM WOW" << std::endl;
		for (auto &storage_id : sys->writeComponentAccess) {
			if (!_components.contains(storage_id)) {
				_components.insert({storage_id, std::vector<std::unique_ptr<Storable>>()});
			}
			sys->registerComponentStorage(storage_id, _components.at(storage_id));
		}
		std::cerr << "BEFORE DAMN REGISTER" << std::endl;
		for (auto &storage_id : sys->writeRessourceAccess) {
			if (!_ressources.contains(storage_id)) {
				/* TODO: Use specialized error */
				std::cerr << "NO RESSOURCE" << std::endl;
				throw std::runtime_error("Ressource not yet registered");
			}
			std::cerr << "YESS" << std::endl;
			sys->registerRessourceStorage(storage_id, *_ressources.at(storage_id));
		}
		sys->onStart();
		_dispatcher._systems.push_back(std::move(sys));
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

	void World::removeComponent(std::unique_ptr<Storable> &component)
	{
		try {
			auto &storage = _components.at(component->UUID);
			auto it = std::find(storage.begin(), storage.end(), component);
			storage.erase(it);
		} catch(std::out_of_range e) {
			/* TODO: handle exception */
		}
	}

	void World::run()
	{
		while (!states.empty()) {
			auto currentStateUuid = states.current().getUUID();
			states.current().onUpdate();
			for (auto &sys : _dispatcher._systems) {
				if (states.empty() || states.current().getUUID() != currentStateUuid) {
					break;
				}
				if (sys->executeOnAllStates || sys->executeOnState.contains(currentStateUuid)) {
					sys->run();
				}
			}
			this->eventsCtx.dispatchEvents();
			this->entities.processRemoval();
		}
		this->entities.removeAll();
		this->entities.processRemoval();
	}
}
