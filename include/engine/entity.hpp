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
#include <memory>
#include "concepts_impl.hpp"
#include "storable.hpp"

namespace Engine {
	template <typename Item>
	class Component;
	class World;

	class Entity
	{
	public:
		Entity() = delete;
		Entity(int64_t id, World &world) : id(id), _world(world) {}
		Entity(const Entity &);
		~Entity() = default;

		template <typename T, typename ... Args> requires derived_from<T, Component<T>>
		Entity &addComponent(Args && ...args)
		{
			std::unique_ptr<Component<T>> instance = std::make_unique<T>(std::forward<Args>(args)...);

			instance->initEntityId(id);
			std::unique_ptr<Storable> store = std::move(instance);
			this->processComponent(store);
			return *this;
		}

		const std::unordered_set<int64_t> &boundComponents() const noexcept { return _boundComponentsType; }
		const int64_t id;

	private:
		void processComponent(std::unique_ptr<Storable> &);

		World &_world;
		std::mutex _componentProcess;
		std::unordered_set<int64_t> _boundComponentsType;
	};
}

#endif /* end of include guard: ENTITY_HPP_K21ZN9ZT */
