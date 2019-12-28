/*
** EPITECH PROJECT, 2019
** player
** File description:
** Representation of a player system
*/

#ifndef PLAYER_HPP_4DPEQCJA
#define PLAYER_HPP_4DPEQCJA


#include "engine/prelude.hpp"
#include "render/events.hpp"
#include "render/ressources.hpp"
#include "render/sprite_component.hpp"
#include "engine/built_in/component/position.hpp"
#include "r-type/component/player.hpp"

using Engine::Component;
using Engine::System;
using Engine::EventHandler;
using Engine::Render::KeystrokeEvent;

class PlayerSystem :
	public Engine::System,
	public Engine::EventHandler<KeystrokeEvent>
{
	using Window = Engine::Render::WindowRessource;
public:
	PlayerSystem() = delete;
	PlayerSystem(World &world) : System(world,
			{world.uuidCtx.get<PlayerComponent>(),
			world.uuidCtx.get<Engine::PositionComponent>(),
			world.uuidCtx.get<Engine::Render::SpriteComponent>()
			},
			{
				world.uuidCtx.get<Window>()
			}),
		EventHandler<KeystrokeEvent>(world)
		{}

	void run() final;
	void onStart() final;
	void handle(KeystrokeEvent const &) final;

private:
	void handleMoves();
	void adjustPositionToWindowBounds(Engine::PositionComponent &player_pos);
	void shoot();
	enum Arrows {LEFT, UP, DOWN, RIGHT, SIZE};
	bool _arrows[Arrows::SIZE] = {false};
	const float MOVE_SPEED = 8;
};



#endif /* end of include guard: PLAYER_HPP_4DPEQCJA */
