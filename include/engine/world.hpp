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

namespace Engine {

	class Component;
	class Entity;

	class World
	{
	public:
		World() = delete;
		~World() = default;
		World(int); //TODO replace with actual state class

		void registerSystem();
		void registerRessource();
		Entity &createEntity();
		void storeComponent(Component &);
		void run();

		UUID uuidGenerator;

	private:

		//dispatcher
		EntityStorage _entities;
		std::unordered_map<int64_t, std::vector<Component>> _components;
		//ressourceStorage
	};
}

#endif /* end of include guard: WORLD_HPP_FORTBZIN */
