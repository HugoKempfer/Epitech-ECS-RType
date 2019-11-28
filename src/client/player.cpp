/*
** EPITECH PROJECT, 2019
** player
** File description:
** Player managament
*/

#include "client/player.hpp"
#include "render/events.hpp"
#include "engine/built_in/position.hpp"
#include "render/sprite_component.hpp"

void PlayerSystem::run()
{
	this->handleMoves();
}

void PlayerSystem::handleMoves()
{
	auto &player_pos = _world.entities.query(*this).with<PlayerComponent>()
		.with<Engine::PositionComponent>().getIntersection()[0]
		.getComponent<Engine::PositionComponent>();

	if (_arrows[UP]) {
		player_pos.pos_y -= MOVE_SPEED;
	}
	if (_arrows[DOWN]) {
		player_pos.pos_y += MOVE_SPEED;
	}
	if (_arrows[LEFT]) {
		player_pos.pos_x -= MOVE_SPEED;
	}
	if (_arrows[RIGHT]) {
		player_pos.pos_x += MOVE_SPEED;
	}
}

void PlayerSystem::handle(KeystrokeEvent const &event)
{
	using Engine::Render::Keyboard;
	bool keyState = event.actionType == KeystrokeEvent::KEY_PRESSED ? true : false;

	switch (event.key.code) {
		case sf::Keyboard::Left:
			_arrows[LEFT] = keyState;
			break;
		case sf::Keyboard::Right:
			_arrows[RIGHT] = keyState;
			break;
		case sf::Keyboard::Up:
			_arrows[UP] = keyState;
			break;
		case sf::Keyboard::Down:
			_arrows[DOWN] = keyState;
			break;
		default:
			break;
	}
}

void PlayerSystem::onStart()
{
	_world.entities.add().addComponent<PlayerComponent>(_world)
		.addComponent<Engine::PositionComponent>(_world)
		.addComponent<Engine::Render::SpriteComponent>(_world, "Damn.png", 50, 50, 4);
}
