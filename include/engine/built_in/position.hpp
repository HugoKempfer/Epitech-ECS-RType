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
		PositionComponent(World &world) : Component<PositionComponent>(world) {}
		~PositionComponent() = default;

		float pos_x;
		float pos_y;
	};
} /* Engine */

#endif /* end of include guard: POSITION_HPP_QSJBKLEA */
