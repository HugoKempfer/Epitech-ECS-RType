#include <iostream>
#include "render/window.hpp"
#include "render/sprite_component.hpp"
#include "render/ressources.hpp"
#include "engine/system.hpp"
#include "engine/query.hpp"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

void damn()
{
	std::cout << "DAMN" << std::endl;
}

namespace Engine::Render
{

	/*template <class T> void swap (T& a, T& b)
	{
		T c(std::move(a)); a=std::move(b); b=std::move(c);
	}*/

	void RenderSystem::run()
	{
		std::vector<ToRender> entity_vec;

		auto entities = _world.entities.query(*this)
			.with<PositionComponent>()
			.with<SpriteComponent>().getIntersection();
		auto &window = this->getRessource<WindowRessource>().window;

		for (auto &entity : entities) {
			ToRender entityToSort = ToRender(entity.getComponent<PositionComponent>(), entity.getComponent<SpriteComponent>());
			entity_vec.push_back(entityToSort);
		}

		// ensure that entities are rendered with respect to their zIndex
		std::sort(entity_vec.begin(), entity_vec.end(), [](ToRender &entityA, ToRender &entityB) {
		  return entityA.sprite.zIndex < entityB.sprite.zIndex;
		  });

		window.clear(sf::Color::Black);
		for (auto &sorted_entity : entity_vec) {
			if (sorted_entity.sprite.isVisible) {
				window.draw(this->getSprite(sorted_entity));
			}
		}
		window.display();
	}

	sf::Sprite &RenderSystem::processSprite(ToRender &entity, sf::Sprite &sprite)
	{
		const auto &position = entity.pos;
		auto &spriteComp = entity.sprite;

		sprite.setPosition({position.pos_x, position.pos_y});
		if (spriteComp.framesNb > 1) {
			sprite.setTextureRect(sf::IntRect(
						(spriteComp.currentFrame - 1) * spriteComp.width,
						0,
						spriteComp.width,
						spriteComp.height));
			if (spriteComp.currentFrame == spriteComp.framesNb) {
				spriteComp.currentFrame = 1;
			} else {
				++spriteComp.currentFrame;
			}
		}
		return sprite;
	}

	sf::Sprite &RenderSystem::getSprite(ToRender &entity)
	{
		const auto &path = entity.sprite.texturePath;
		if (!_sprites.contains(path)) {
			_textures.insert({path, sf::Texture()});
			auto &tex = _textures.at(path);
			tex.loadFromFile(path);
			_sprites.insert({path, sf::Sprite(tex)});
		}
		return this->processSprite(entity, _sprites.at(path));
	}
} /* Engine::Render */
