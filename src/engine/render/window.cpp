/*
** EPITECH PROJECT, 2019
** window
** File description:
** Open and manage window instance
*/

#include <iostream>
#include "render/window.hpp"
#include "engine/world.hpp"

namespace Engine::Render
{
	void WindowSystem::run()
	{
		sf::Event event;

		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_world.eventsCtx.publish<KeystrokeEvent>(_world, KeystrokeEvent::CLOSE);
			}
			/* TODO: extract windows event and broadcast on channels */
		}
	}

} /* Engine::Render */
