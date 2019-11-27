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
	class SpriteComponent : public Component<SpriteComponent>
	{
	public:
		SpriteComponent() = delete;
		SpriteComponent(World &world, std::string texturePath) :
			Component<SpriteComponent>(world),
			texturePath(texturePath)
		{}
		virtual ~SpriteComponent() = default;

		const std::string texturePath;
		bool isVisible = true;
	};

} /* Engine::Render */

#endif /* end of include guard: SPRITE_COMPONENT_HPP_CT2V3ZPE */
