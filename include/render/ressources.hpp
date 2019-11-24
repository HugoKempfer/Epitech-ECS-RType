/*
** EPITECH PROJECT, 2019
** ressources
** File description:
** Built-in engine ressources
*/

#ifndef RESSOURCES_HPP_KBW0ATIM
#define RESSOURCES_HPP_KBW0ATIM

#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/ressource.hpp"
#include "engine/world.hpp"

namespace Engine::Render
{
	class WindowRessource : public Ressource<WindowRessource>
	{
	public:
		WindowRessource() = delete;
		WindowRessource(World &world) : Ressource<WindowRessource>(world) {}
		~WindowRessource() = default;

		sf::RenderWindow window;
	};
} /* Engine::Render */

#endif /* end of include guard: RESSOURCES_HPP_KBW0ATIM */
