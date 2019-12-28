/*
** EPITECH PROJECT, 2019
** enemy
** File description:
** Representation of enemy component
*/

#ifndef ENEMY_HPP_ODHVXF7N
#define ENEMY_HPP_ODHVXF7N

#include "engine/prelude.hpp"

using Engine::World;
using Engine::Component;

namespace Engine
{
	struct EnemyComponent: public Component<EnemyComponent>
	{
		EnemyComponent() = delete;
		EnemyComponent(World &world, int health):
			Component<EnemyComponent>(world), health(health) {}
		~EnemyComponent() = default;

		int health;
	};
}

#endif /* end of include guard: ENEMY_HPP_ODHVXF7N */
