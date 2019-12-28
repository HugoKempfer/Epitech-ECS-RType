/*
** EPITECH PROJECT, 2019
** player
** File description:
** Player managament
*/

#include "client/map.hpp"
#include "render/events.hpp"
#include "engine/built_in/position.hpp"

void MapSystem::run()
{
	this->moveMap();
}

void MapSystem::moveMap()
{
	auto &map_pos = _world.entities.query(*this).with<MapComponent>()
		.with<Engine::PositionComponent>().getIntersection()[0]
		.getComponent<Engine::PositionComponent>();
	
	map_pos.pos_x -= MOVE_SPEED;
}

void MapSystem::onStart()
{
	const auto window_size = this->getRessource<Window>().window.getSize();

	_world.entities.add().addComponent<MapComponent>(_world)
		.addComponent<Engine::PositionComponent>(_world)
		.addComponent<Engine::Render::SpriteComponent>(_world, "../assets/1288_gamemap1.png", window_size.y, window_size.x);
}
