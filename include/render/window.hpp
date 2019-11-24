/*
** EPITECH PROJECT, 2019
** window
** File description:
** Open and manage window instance
*/

#ifndef WINDOW_HPP_SK6QEY7C
#define WINDOW_HPP_SK6QEY7C

#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>
#include "engine/system.hpp"
#include "engine/world.hpp"
#include "engine/event.hpp"

namespace Engine::Render
{
	class KeystrokeEvent : public Event<KeystrokeEvent>
	{
	public:
		enum Keys {
			CLOSE
		};

		KeystrokeEvent() = delete;
		KeystrokeEvent(World &world, Keys key) :
			Event<KeystrokeEvent>(world.uuidCtx),
			key(key)
		{}

		const enum Keys key;
	};

	class WindowSystem : public System
	{
	public:
		WindowSystem (World &world, uint32_t height = 800, uint32_t width = 800) :
			System(world,
					{},
					{}),
			_window(sf::VideoMode(width, height), "wow")
		{}
		~WindowSystem()
		{
			_window.close();
		}

		void run() override;

	private:
		sf::Window  _window;
	};

} /* Engine::Render */


#endif /* end of include guard: WINDOW_HPP_SK6QEY7C */
