/*
** EPITECH PROJECT, 2019
** world
** File description:
** Engine base container
*/

#ifndef WORLD_HPP_FORTBZIN
#define WORLD_HPP_FORTBZIN

#include "game_storage.hpp"

namespace Engine {
	class World
	{
	public:
		World() = delete;
		~World() = default;
		World(int initialState); //TODO replace with actual state class

		void registerSystem();
		void registerRessource();
		void createEntity();
		void run();

	private:
		//dispatcher
		EntityStorage _entities;
		//componentStorage
		//ressourceStorage
	};
}

#endif /* end of include guard: WORLD_HPP_FORTBZIN */
