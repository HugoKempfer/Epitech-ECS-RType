/*
** EPITECH PROJECT, 2019
** entity
** File description:
** game entity representation
*/

#ifndef ENTITY_HPP_K21ZN9ZT
#define ENTITY_HPP_K21ZN9ZT

#include <iostream>
#include <unordered_set>
#include <mutex>
#include "concepts_impl.hpp"

namespace Engine {
	class Component;
	class World;

	class Entity
	{
	public:
		Entity() = delete;
		Entity(int64_t id, World &world) : _id(id), _world(world) {}
		Entity(const Entity &);
		~Entity() = default;

		template <typename T, typename ... Args> requires derived_from<T, Component>
		Entity &addComponent(Args && ...args)
		{
			T instance = T(std::forward<Args>(args)...);

			this->processComponent(instance);
			return *this;
		}

	private:
		void processComponent(Component &);

		const int64_t _id;
		World &_world;
		std::mutex _componentProcess;
		std::unordered_set<int64_t> _boundComponentsType;
	};
}

#endif /* end of include guard: ENTITY_HPP_K21ZN9ZT */
