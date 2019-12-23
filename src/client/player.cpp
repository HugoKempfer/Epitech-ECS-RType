/*
** EPITECH PROJECT, 2019
** player
** File description:
** Player managament
*/

#include "client/player.hpp"
#include "render/events.hpp"
#include "engine/built_in/position.hpp"
#include "client/bullet.hpp"

void PlayerSystem::run()
{
	this->handleMoves();
}

void PlayerSystem::adjustPositionToWindowBounds(Engine::PositionComponent &player_pos) {

	const auto window_size = this->getRessource<Window>().window.getSize();
	const auto &sprite_component = _world.entities.query(*this).with<PlayerComponent>()
		.with<Engine::Render::SpriteComponent>()
		.getIntersection()[0]
		.getComponent<Engine::Render::SpriteComponent>();

	if (player_pos.pos_y < 0) {
		player_pos.pos_y = 0;
	}
	if (player_pos.pos_x < 0) {
		player_pos.pos_x = 0;
	}
	if (player_pos.pos_y > (window_size.y - sprite_component.height)) {
		player_pos.pos_y = window_size.y - sprite_component.height;
	}
	if (player_pos.pos_x > (window_size.x - sprite_component.width)) {
		player_pos.pos_x = window_size.x - sprite_component.width;
	}
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
	this->adjustPositionToWindowBounds(player_pos);
}

void PlayerSystem::shoot()
{
	using Engine::PositionComponent;
	using Engine::Render::SpriteComponent;

	const auto player = _world.entities.query(*this)
		.with<PlayerComponent>()
		.with<PositionComponent>()
		.getIntersection()[0].getComponent<PositionComponent>();

	_world.entities.add()
		.addComponent<BulletComponent>(_world, BulletComponent::RIGHT)
		.addComponent<Engine::PositionComponent>(_world, player.pos_x, player.pos_y)
		.addComponent<SpriteComponent>(_world, "Damn.png", 15, 20);
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
		case sf::Keyboard::Space:
			if (event.actionType == KeystrokeEvent::KEY_PRESSED) {
				this->shoot();
			}
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
