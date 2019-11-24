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
#include "render/ressources.hpp"

namespace Engine::Render
{

	class WindowSystem : public System
	{
	public:
		WindowSystem() = delete;
		WindowSystem (World &world, uint32_t height = 800, uint32_t width = 800) :
			System(world,
					{},
					{world.uuidCtx.get<WindowRessource>()}),
			_height(height),
			_width(width)
		{}

		void onStart() override
		{
			auto &wRessource = this->getRessource<WindowRessource>();

			wRessource.window.create(sf::VideoMode(_width, _height), "damn");
		}

		~WindowSystem()
		{
			auto &wRessource = this->getRessource<WindowRessource>();

			wRessource.window.close();
		}

		void run() override;

	private:
		void handleEvent(sf::Event &event);
		const int _height;
		const int _width;
	};

} /* Engine::Render */


#endif /* end of include guard: WINDOW_HPP_SK6QEY7C */
