/*
** EPITECH PROJECT, 2019
** component
** File description:
** Store game logic data, bound to an entity
*/

#ifndef COMPONENT_HPP_ZX9GAJK5
#define COMPONENT_HPP_ZX9GAJK5

#include <iostream>
#include <atomic>
#include "concepts_impl.hpp"
#include "world.hpp"

namespace Engine
{

	class Component
	{
	public:
		Component() = delete;

		template <typename Child> requires derived_from<Child, Component>
		Component(World &world, int64_t entityId)
			: _world(world), _entityId(entityId), componentTypeUUID(_world.uuidGenerator.get<Child>())
		{}

		virtual ~Component();

		const int64_t componentTypeUUID;

	private:
		World &_world;
		const int64_t _entityId;
	};
} /* Engine */

#endif /* end of include guard: COMPONENT_HPP_ZX9GAJK5 */
