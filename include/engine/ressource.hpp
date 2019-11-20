/*
** EPITECH PROJECT, 2019
** ressource
** File description:
** Storage for game logic data unrelated to entities
*/

#ifndef RESSOURCE_HPP_TXQGAZAL
#define RESSOURCE_HPP_TXQGAZAL

#include "storable.hpp"
#include "world.hpp"

namespace Engine
{
	template <typename T>
	class Ressource : public Storable
	{
	public:
		Ressource() = delete;
		Ressource(World &world) : Storable(world.uuidCtx, world.uuidCtx.get<T>()) {}

		virtual ~Ressource() = default;
	};

} /* Engine */

#endif /* end of include guard: RESSOURCE_HPP_TXQGAZAL */
