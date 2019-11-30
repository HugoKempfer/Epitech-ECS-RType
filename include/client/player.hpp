/*
** EPITECH PROJECT, 2019
** player
** File description:
** Representation of a player
*/

#ifndef PLAYER_HPP_CQVWA8K6
#define PLAYER_HPP_CQVWA8K6

#include "engine/prelude.hpp"
#include "render/events.hpp"
#include "engine/built_in/position.hpp"

using Engine::Component;
using Engine::World;
using Engine::EventHandler;
using Engine::Render::KeystrokeEvent;

struct PlayerComponent : public Component<PlayerComponent>
{
	PlayerComponent() = delete;
	PlayerComponent(World &world) : Component<PlayerComponent>(world) {}
	~PlayerComponent() = default;
};

class PlayerSystem :
	public Engine::System,
	public Engine::EventHandler<KeystrokeEvent>
{
public:
	PlayerSystem() = delete;
	PlayerSystem(World &world) : System(world,
			{world.uuidCtx.get<PlayerComponent>(),
			world.uuidCtx.get<Engine::PositionComponent>()
			},
			{}),
		EventHandler<KeystrokeEvent>(world)
		{}

	void run() final;
	void onStart() final;
	void handle(KeystrokeEvent const &) final;

private:
	void handleMoves();
	void shoot();
	enum Arrows {LEFT, UP, DOWN, RIGHT, SIZE};
	bool _arrows[Arrows::SIZE] = {false};
	const float MOVE_SPEED = 8;
};

#endif /* end of include guard: PLAYER_HPP_CQVWA8K6 */
