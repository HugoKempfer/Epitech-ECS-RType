/*
** EPITECH PROJECT, 2019
** bullet
** File description:
** Representation of a laser shot
*/

#ifndef DAMAGE_SYSTEM_HPP_YKMU68RC
#define DAMAGE_SYSTEM_HPP_YKMU68RC

#include "engine/prelude.hpp"
#include "render/ressources.hpp"
#include "engine/built_in/component/enemy.hpp"
#include "engine/built_in/component/hitbox.hpp"
#include "engine/built_in/component/position.hpp"
#include "client/player.hpp"

using Engine::System;

class DamageSystem : public System
{
	public:
		DamageSystem() = delete;
		DamageSystem(World &world) :
			System(world, {world.uuidCtx.get<Engine::PositionComponent>(), world.uuidCtx.get<PlayerComponent>(), world.uuidCtx.get<EnemyComponent>()}, {}) {}
		virtual ~DamageSystem() = default;

		void run() final;

};

#endif /* end of include guard: DAMAGE_SYSTEM_HPP_YKMU68RC */
