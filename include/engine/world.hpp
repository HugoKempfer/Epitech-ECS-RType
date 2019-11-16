/*
** EPITECH PROJECT, 2019
** world
** File description:
** Engine base container
*/

#ifndef WORLD_HPP_FORTBZIN
#define WORLD_HPP_FORTBZIN

#include <unordered_map>
#include <vector>
#include <memory>
#include "game_storage.hpp"
#include "concepts_impl.hpp"
#include "uuid.hpp"
#include "storable.hpp"
#include "state.hpp"

namespace Engine {

	class Entity;

	class World
	{
	public:
		World();
		~World() = default;

		void registerSystem();
		void registerRessource();
		Entity &createEntity();
		Entity &getEntity(int64_t);
		void storeComponent(Storable &);
		void run();

		UUIDContext uuidCtx;

	private:
		//dispatcher
		StateMachine _states;
		EntityStorage _entities;
		std::unordered_map<int64_t, std::vector<Storable>> _components;
		//ressourceStorage
	};
}

#endif /* end of include guard: WORLD_HPP_FORTBZIN */
