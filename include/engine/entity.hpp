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
#include <unordered_map>
#include <mutex>
#include <memory>
#include "concepts_impl.hpp"
#include "storable.hpp"
#include "uuid.hpp"

namespace Engine {
	template <typename Item>
	class Component;
	class World;

	class Entity
	{
	public:
		Entity() = delete;
		Entity(int64_t id, World &world);
		Entity(const Entity &);
		~Entity();

		template <typename T, typename ... Args> requires derived_from<T, Component<T>>
		Entity &addComponent(Args && ...args)
		{
			std::unique_ptr<Component<T>> instance = std::make_unique<T>(std::forward<Args>(args)...);

			instance->initEntityId(id);
			std::unique_ptr<Storable> store = std::move(instance);
			this->processComponentInsertion(store);
			return *this;
		}

		template <typename T, typename ... Args> requires derived_from<T, Component<T>>
		void removeComponent()
		{
			std::lock_guard<std::mutex> lock(_componentProcess);
			auto uuid = _uuidCtx.get<T>();

			auto &component = _componentsRef.at(uuid);
			_boundComponentsType.erase(uuid);
			_componentsRef.erase(uuid);
			this->processComponentRemoval(component);
		}

		const std::unordered_set<int64_t> &boundComponents() const noexcept { return _boundComponentsType; }
		const int64_t id;

	private:
		void processComponentInsertion(std::unique_ptr<Storable> &);
		void processComponentRemoval(std::unique_ptr<Storable> &);

		World &_world;
		UUIDContext &_uuidCtx;
		std::mutex _componentProcess;
		std::unordered_set<int64_t> _boundComponentsType;
		std::unordered_map<int64_t, std::reference_wrapper<std::unique_ptr<Storable>>> _componentsRef;
	};
}

#endif /* end of include guard: ENTITY_HPP_K21ZN9ZT */
