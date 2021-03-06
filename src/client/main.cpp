/*
** EPITECH PROJECT, 2019
** main
** File description:
** RType graphical client
*/

#include <iostream>
#include <memory>

#include <SFML/Window.hpp>

#include "engine/prelude.hpp"
#include "render/window.hpp"
#include "render/events.hpp"
#include "render/sprite_component.hpp"
#include "render/bundles.hpp"
#include "engine/built_in/component/position.hpp"
#include "r-type/system/player.hpp"
#include "r-type/system/bullet.hpp"
#include "r-type/system/map.hpp"

void test_engine();
void damn();

using namespace Engine;
using namespace Engine::Render;

class InitState : public State<InitState>, public EventHandler<SignalEvent>{
public:
	InitState() = delete;
	InitState(World &world) :
		State<InitState>(world),
		EventHandler<SignalEvent>(world)
	{}

	void handle(SignalEvent const &event) final
	{
		if (event.signal == SignalEvent::CLOSE) {
			_world.states.pop();
		}
	}
};

int main([[maybe_unused]]int argc, [[maybe_unused]]char *argv[])
{
	World world;

	world.useBundle<RenderBundle>();
	world.registerSystem<PlayerSystem>(world);
	world.registerSystem<BulletSystem>(world);
	world.registerSystem<MapSystem>(world);
	world.states.push<InitState>(world);
	world.run();
	return 0;
}
