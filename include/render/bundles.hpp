/*
** EPITECH PROJECT, 2019
** bundles
** File description:
** Built-in bundles for engine render
*/

#ifndef BUNDLES_HPP_3GP8QR2L
#define BUNDLES_HPP_3GP8QR2L

#include "engine/bundle.hpp"

namespace Engine::Render
{
	class RenderBundle : public Bundle
	{
	public:
		RenderBundle() = delete;
		RenderBundle(World &world) : Bundle(world) {}
		void registerRessources(World &world) final;
		void registerSystems(World &world) final;
	};
} /* Engine::Render */

#endif /* end of include guard: BUNDLES_HPP_3GP8QR2L */
