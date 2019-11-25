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
#include "definitions.hpp"
#include "game_storage.hpp"
#include "concepts_impl.hpp"
#include "uuid.hpp"
#include "storable.hpp"
#include "state_machine.hpp"
#include "dispatcher.hpp"
#include "event_context.hpp"

namespace Engine {

	class Entity;
	class Storable;

	template <typename T>
	class Ressource;


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

		template <typename T, typename ... Args> requires derived_from<T, Ressource<T>>
		World &registerRessource(Args && ...args)
		{
			auto res = std::make_unique<T>(std::forward<Args>(args)...);

			_ressources.insert({res->UUID, std::move(res)});
			return *this;
		}

		//Don't directly call this method => Deprecated
		void storeComponent(std::unique_ptr<Storable> &);

		//Don't directly call this method => Deprecated
		void removeComponent(std::unique_ptr<Storable> &);

		//Launch the event loop
		void run();

		UUIDContext uuidCtx;
		EventCtx eventsCtx;

		EntityStorage entities;
		StateMachine states;

	private:
		void processSystemRegistration(std::unique_ptr<System> &);

		Dispatcher _dispatcher;
		ComponentStorage _components;
		RessourceStorage _ressources;
	};
}

#endif /* end of include guard: WORLD_HPP_FORTBZIN */
