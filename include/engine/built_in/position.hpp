/*
** EPITECH PROJECT, 2019
** position
** File description:
** Built-in component for position
*/

#ifndef POSITION_HPP_QSJBKLEA
#define POSITION_HPP_QSJBKLEA

#include "engine/world.hpp"
#include "engine/component.hpp"

namespace Engine
{
	class PositionComponent : public Component<PositionComponent>
	{
	public:
		PositionComponent() = delete;
		PositionComponent(World &world, float x = 0,
				float y = 0) : Component<PositionComponent>(world),
		pos_x(x), pos_y(y)
		{}
		~PositionComponent() = default;

		PositionComponent &operator=(const PositionComponent &other) {
			pos_x = other.pos_x;
			pos_y = other.pos_y;

			return *this;
		}

		float pos_x;
		float pos_y;
	};
} /* Engine */

#endif /* end of include guard: POSITION_HPP_QSJBKLEA */
