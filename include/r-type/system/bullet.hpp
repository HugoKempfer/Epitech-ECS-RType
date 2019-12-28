/*
** EPITECH PROJECT, 2019
** bullet
** File description:
** Representation of a laser shot
*/

#ifndef BULLET_HPP_NY9CUXLE
#define BULLET_HPP_NY9CUXLE


#include "engine/prelude.hpp"
#include "engine/built_in/component/position.hpp"
#include "render/ressources.hpp"
#include "r-type/component/bullet.hpp"

class BulletSystem : public Engine::System
{
	using Window = Engine::Render::WindowRessource;

public:
	BulletSystem() = delete;
	BulletSystem(World &world) :
		Engine::System(world,
				{world.uuidCtx.get<Engine::PositionComponent>(),
				world.uuidCtx.get<BulletComponent>()},
				{world.uuidCtx.get<Window>()}
				) {}
	virtual ~BulletSystem() = default;

	void run() final;

	const float MOVE_INC = 15;

private:
	void processMoves();
};

#endif /* end of include guard: BULLET_HPP_NY9CUXLE */
