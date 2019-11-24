/*
** EPITECH PROJECT, 2019
** sprite_component
** File description:
** Built-in sprite component
*/

#ifndef SPRITE_COMPONENT_HPP_CT2V3ZPE
#define SPRITE_COMPONENT_HPP_CT2V3ZPE

#include "engine/component.hpp"

namespace Engine::Render
{
	class SpriteComponent : Component<SpriteComponent>
	{
	public:
		SpriteComponent() = delete;
		SpriteComponent(World &world, std::string &spritePath) :
			Component<SpriteComponent>(world),
			spritePath(spritePath)
		{}
		virtual ~SpriteComponent() = default;

		const std::string spritePath;
		bool isVisible = true;
	};

} /* Engine::Render */

#endif /* end of include guard: SPRITE_COMPONENT_HPP_CT2V3ZPE */
