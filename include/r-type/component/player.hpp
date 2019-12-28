/*
** EPITECH PROJECT, 2019
** player
** File description:
** Representation of a player
*/

#ifndef PLAYER_HPP_CQVWA8K6
#define PLAYER_HPP_CQVWA8K6

#include "engine/prelude.hpp"
#include "render/events.hpp"
#include "engine/built_in/component/position.hpp"

using Engine::Component;
/* using Engine::World; */
using Engine::EventHandler;
using Engine::Render::KeystrokeEvent;

struct PlayerComponent : public Component<PlayerComponent>
{
	PlayerComponent() = delete;
	PlayerComponent(World &world) : Component<PlayerComponent>(world) {}
	~PlayerComponent() = default;
};


#endif /* end of include guard: PLAYER_HPP_CQVWA8K6 */
