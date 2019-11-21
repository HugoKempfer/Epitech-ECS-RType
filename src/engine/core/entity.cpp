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
		_boundComponentsType(old._boundComponentsType),
		_uuidCtx(_world.uuidCtx)
	{}

	Entity::Entity(int64_t id, World &world) :
		id(id), _world(world), _uuidCtx(world.uuidCtx)
	{}

	void Entity::processComponentInsertion(std::unique_ptr<Storable> &component)
	{
		std::lock_guard<std::mutex> lock(_componentProcess);

		_boundComponentsType.insert(component->UUID);
		_componentsRef.insert({component->UUID, component});
		_world.storeComponent(component);
	}

	void Entity::processComponentRemoval(std::unique_ptr<Storable> &component)
	{
		_world.removeComponent(component);
	}

} /* Engine */
