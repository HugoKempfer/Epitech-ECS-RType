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
		SpriteComponent(World &world, std::string texturePath, int height, int width, int framesNb = 1, int zIndex = highestDepth) :
			Component<SpriteComponent>(world),
			texturePath(texturePath),
			height(height),
			width(width),
			framesNb(framesNb),
			zIndex(zIndex)
		{
			if (zIndex > SpriteComponent::highestDepth) {
				highestDepth = zIndex + 1;
			}
		}
		virtual ~SpriteComponent() = default;
		SpriteComponent &operator=(const SpriteComponent &other) {
			texturePath = std::string(other.texturePath);
			isVisible = other.isVisible;
			height = other.height;
			width = other.width;
			framesNb = other.framesNb;
			currentFrame = other.currentFrame;
			highestDepth = other.highestDepth;
			zIndex = other.zIndex;

			return *this;
		}

		std::string texturePath;
		bool isVisible = true;
		int height;
		int width;
		int framesNb;
		int currentFrame = 1;
		static int highestDepth;
		int zIndex = 0;
	};

} /* Engine::Render */

#endif /* end of include guard: SPRITE_COMPONENT_HPP_CT2V3ZPE */
