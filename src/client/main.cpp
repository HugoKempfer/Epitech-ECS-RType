/*
** EPITECH PROJECT, 2019
** main
** File description:
** RType graphical client
*/

#include <iostream>
#include <SFML/Window.hpp>
#include <memory>
#include "engine/world.hpp"
#include "engine/state.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "render/window.hpp"
#include "render/events.hpp"
#include "render/sprite_component.hpp"
#include "engine/built_in/position.hpp"

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

	void onStart() final
	{
		std::cout << "STARTED" << std::endl;
		_world.entities.add().addComponent<SpriteComponent>(_world, "./steph.jpg")
			.addComponent<PositionComponent>(_world, 100, 100);
	}

	void onStop() final
	{
		std::cout << "BYE" << std::endl;
	}

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
	world.registerRessource<WindowRessource>(world);
	world.registerSystem<WindowSystem>(world, 200, 30);
	world.registerSystem<RenderSystem>(world);
	world.run();
	return 0;
}
