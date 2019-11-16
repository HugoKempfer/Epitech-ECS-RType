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
		: id(old.id), _world(old._world), _boundComponentsType(old._boundComponentsType)
	{}

	void Entity::processComponent(Storable &component)
	{
		std::lock_guard<std::mutex> lock(_componentProcess);

		_world.storeComponent(component);
		_boundComponentsType.insert(component.UUID);
	}

} /* Engine */
