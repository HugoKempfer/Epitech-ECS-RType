/*
** EPITECH PROJECT, 2019
** bullet
** File description:
** Representation of a laser shot
*/

#include "client/bullet.hpp"

void BulletSystem::run()
{
	this->processMoves();
}

void BulletSystem::processMoves()
{
	const auto window_size = this->getRessource<Window>().window.getSize();
	auto entities = _world.entities.query(*this)
		.with<Engine::PositionComponent>()
		.with<BulletComponent>().getIntersection();

	for (auto &entity : entities) {
		auto &pos = entity.getComponent<Engine::PositionComponent>();
		switch (entity.getComponent<BulletComponent>().direction) {
			case BulletComponent::LEFT:
				pos.pos_x -= MOVE_INC;
				break;
			case BulletComponent::RIGHT:
				pos.pos_x += MOVE_INC;
				break;
		}
		if (pos.pos_x > window_size.x || pos.pos_x < 0) {
			_world.entities.doRemove(entity.entity.id);
		}
	}
}
