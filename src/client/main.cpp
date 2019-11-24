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

void test_engine();
void damn();

using namespace Engine;
using namespace Engine::Render;

class InitState : public State<InitState>, public EventHandler<KeystrokeEvent> {
public:
	InitState() = delete;
	InitState(World &world) :
		State<InitState>(world),
		EventHandler<KeystrokeEvent>(world)
	{}

	void onStart() final
	{
		std::cout << "STARTED" << std::endl;
	}

	void onStop() final
	{
		std::cout << "BYE" << std::endl;
	}

	void handle(KeystrokeEvent const &event) final
	{
		switch (event.key) {
			case Render::KeystrokeEvent::CLOSE:
				std::cout << "CLOSE" << std::endl;
				_world.states.pop();
				break;
		}
	}
};

int main(int argc, char *argv[])
{
	World world;

	world.states.push<InitState>(world);
	world.registerSystem<WindowSystem>(world, 200, 30);
	world.run();
	return 0;
}
