/*
** EPITECH PROJECT, 2019
** window
** File description:
** Open and manage window instance
*/

#include <iostream>
#include "render/window.hpp"
#include "engine/world.hpp"
#include "render/events.hpp"

namespace Engine::Render
{
	void WindowSystem::handleEvent(sf::Event &event)
	{
		switch (event.type) {
			case sf::Event::KeyPressed:
				[[fallthrough]];
			case sf::Event::KeyReleased:
				[[fallthrough]];
			case sf::Event::TextEntered:
				_world.eventsCtx.publish<KeystrokeEvent>(_world, event);
				break;
			case sf::Event::MouseButtonPressed:
				[[fallthrough]];
			case sf::Event::MouseMoved:
				[[fallthrough]];
			case sf::Event::MouseButtonReleased:
				_world.eventsCtx.publish<MouseEvent>(_world, event);
				break;
			case sf::Event::Closed:
				[[fallthrough]];
			case sf::Event::LostFocus:
				[[fallthrough]];
			case sf::Event::GainedFocus:
				_world.eventsCtx.publish<SignalEvent>(_world, event.type);
				break;
			default:
				break;
		}
	}

	void WindowSystem::run()
	{
		sf::Event event;

		while (_window.pollEvent(event)) {
			this->handleEvent(event);
			/* TODO: extract windows event and broadcast on channels */
		}
	}

} /* Engine::Render */
