/*
** EPITECH PROJECT, 2019
** entity
** File description:
** game entity representation
*/

#include <mutex>
#include <unordered_set>
#include "engine/entity.hpp"
#include "engine/world.hpp"
#include "engine/component.hpp"

namespace Engine
{
	Entity::Entity(const Entity &old)
		: id(old.id),
		_world(old._world),
		_uuidCtx(_world.uuidCtx),
		_boundComponentsType(old._boundComponentsType)
	{}

	void Entity::onDestroy()
	{
		std::lock_guard<std::mutex> lock(_componentProcess);

		for (auto it : _componentsRef) {
			std::cerr << it.second.get().UUID << std::endl;
			this->processComponentRemoval(it.second);
		}
	}

	Entity::Entity(int64_t id, World &world) :
		id(id), _world(world), _uuidCtx(world.uuidCtx)
	{}

	void Entity::processComponentInsertion(std::unique_ptr<Storable> &component)
	{
		std::lock_guard<std::mutex> lock(_componentProcess);

		auto &moved = _world.storeComponent(component);
		_boundComponentsType.insert(moved->UUID);
		_componentsRef.insert({moved->UUID, {*moved}});
	}

	void Entity::processComponentRemoval(Storable &component)
	{
		_world.removeComponent(component);
	}

} /* Engine */
