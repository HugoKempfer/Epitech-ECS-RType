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

	Component(World &world)
		: _world(world), Storable(world.uuidCtx, world.uuidCtx.get<Item>())
	{}
		virtual ~Component() = default;
		void initEntityId(int64_t id)
		{
			if (_entityId == -1) {
				_entityId = id;
			}
		}
		int64_t getEntityId() const noexcept { return _entityId; }

	private:
		World &_world;
		int64_t _entityId = -1;
	};
} /* Engine */

#endif /* end of include guard: COMPONENT_HPP_ZX9GAJK5 */
