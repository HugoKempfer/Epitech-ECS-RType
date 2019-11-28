/*
** EPITECH PROJECT, 2019
** main
** File description:
** RType graphical client
*/

#include <iostream>
#include <SFML/Window.hpp>
#include <memory>
#include "engine/prelude.hpp"
#include "render/window.hpp"
#include "render/events.hpp"
#include "render/sprite_component.hpp"
#include "render/bundles.hpp"
#include "engine/built_in/position.hpp"
#include "client/player.hpp"

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

int main(int argc, char *argv[])
{
	World world;

	world.states.push<InitState>(world);
	world.registerSystem<PlayerSystem>(world);
	world.useBundle<RenderBundle>();
	world.run();
	return 0;
}
