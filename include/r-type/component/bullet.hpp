/*
** EPITECH PROJECT, 2019
** bullet
** File description:
** Representation of a laser shot
*/

#ifndef BULLET_HPP_36MKSLVO
#define BULLET_HPP_36MKSLVO

#include "engine/prelude.hpp"
#include "engine/built_in/component/position.hpp"
#include "render/ressources.hpp"

class BulletComponent : public Engine::Component<BulletComponent>
{
public:
	enum Direction {LEFT, RIGHT};
	BulletComponent() = delete;
	BulletComponent(World &world, Direction direction) :
		Engine::Component<BulletComponent>(world),
		direction(direction)
	{}
	virtual ~BulletComponent() = default;

	Direction direction;
};


#endif /* end of include guard: BULLET_HPP_36MKSLVO */
