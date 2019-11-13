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
#include "storable.hpp"

namespace Engine
{
	template <typename Item>
	class Component : public Storable
	{
	public:
		Component() = delete;

	Component(World &world, int64_t entityId)
		: _world(world), _entityId(entityId), Storable(world.uuidCtx, world.uuidCtx.get<Item>())
	{}
		virtual ~Component();

	private:
		World &_world;
		const int64_t _entityId;
	};
} /* Engine */

#endif /* end of include guard: COMPONENT_HPP_ZX9GAJK5 */
