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
#include "state_machine.hpp"
#include "dispatcher.hpp"

namespace Engine {

	class Entity;
	class Storable;

	class World
	{
	public:
		World();
		~World();

		template <typename T, typename ... Args> requires derived_from<T, System>
		World &registerSystem(Args && ...args)
		{
			std::unique_ptr<System> sys = std::make_unique<T>(std::forward<Args>(args)...);

			this->processSystemRegistration(sys);
			return *this;
		}

		void registerRessource();

		//Don't directly call this method => Deprecated
		void storeComponent(std::unique_ptr<Storable> &);

		//Don't directly call this method => Deprecated
		void removeComponent(std::unique_ptr<Storable> &);
		void run();

		UUIDContext uuidCtx;

		EntityStorage entities;
		StateMachine states;

	private:
		void processSystemRegistration(std::unique_ptr<System> &);

		Dispatcher _dispatcher;
		std::unordered_map<int64_t, std::vector<std::unique_ptr<Storable>>> _components;
		//ressourceStorage
	};
}

#endif /* end of include guard: WORLD_HPP_FORTBZIN */
