/*
** EPITECH PROJECT, 2019
** player
** File description:
** Representation of a player
*/

#ifndef MAP_HPP_JUGTEIMN
#define MAP_HPP_JUGTEIMN

#include "engine/prelude.hpp"
#include "render/events.hpp"
#include "engine/built_in/position.hpp"
#include "render/ressources.hpp"
#include "render/sprite_component.hpp"

using Engine::Component;
using Engine::World;
using Engine::EventHandler;

struct MapComponent : public Component<MapComponent> {
	MapComponent() = delete;
	MapComponent(World &world) : Component<MapComponent>(world) {}
	~MapComponent() = default;
};

class MapSystem : public Engine::System
{
	using Window =  Engine::Render::WindowRessource;
public:
	MapSystem() = delete;
	MapSystem(World &world) :  System(world,
			{world.uuidCtx.get<MapComponent>(),
			 world.uuidCtx.get<Engine::PositionComponent>(),
			 world.uuidCtx.get<Engine::Render::SpriteComponent>()
			},
			{
				world.uuidCtx.get<Window>()
			})
		{}

	void run() final;
	void onStart() final;
	void moveMap();
	//void handle(KeystrokeEvent const &) final;

private:
	const float MOVE_SPEED = 2;
};

#endif /* end of include guard: MAP_HPP_JUGTEIMN */
