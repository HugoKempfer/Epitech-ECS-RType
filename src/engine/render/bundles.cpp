/*
** EPITECH PROJECT, 2019
** bundles
** File description:
** Built-in bundles for engine render
*/

#include "render/ressources.hpp"
#include "render/bundles.hpp"
#include "render/window.hpp"

namespace Engine::Render
{
		void RenderBundle::registerRessources(World &world)
		{
			world.registerRessource<WindowRessource>(world);
		}
		void RenderBundle::registerSystems(World &world)
		{
			world.registerSystem<WindowSystem>(world)
				.registerSystem<RenderSystem>(world);
		}

} /* Engine::Bundle */
