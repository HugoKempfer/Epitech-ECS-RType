/*
** EPITECH PROJECT, 2019
** hitzone
** File description:
** Representation of hitzone
*/

#ifndef HITBOX_HPP_MG5PQT6D
#define HITBOX_HPP_MG5PQT6D

#include "engine/prelude.hpp"

using Engine::World;
using Engine::Component;

namespace Engine
{
	struct HitzoneComponent : public Component<HitzoneComponent>
	{
		HitzoneComponent() = delete;
		HitzoneComponent(World &world, float with, float height):
			Component<HitzoneComponent>(world), with(with), height(height) {}
		~HitzoneComponent() = default;

		float with;
		float height;
	};
}

#endif /* end of include guard: HITBOX_HPP_MG5PQT6D */

