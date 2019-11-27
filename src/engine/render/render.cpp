#include <iostream>
#include "render/window.hpp"
#include "render/sprite_component.hpp"
#include "render/ressources.hpp"
#include "engine/system.hpp"
#include "engine/query.hpp"

void damn()
{
	std::cout << "DAMN" << std::endl;
}

namespace Engine::Render
{
	void RenderSystem::run()
	{
		/* auto sprites = this->getComponents<SpriteComponent>(); */
		auto entities = _world.entities.query(*this)
			.with<PositionComponent>()
			.with<SpriteComponent>().getIntersection();
		auto &window = this->getRessource<WindowRessource>().window;

		window.clear(sf::Color::Black);
		for (auto &entity : entities) {
			window.draw(this->getSprite(entity));
		}
		/* TODO: Render every sprite component */
	}

	sf::Sprite &RenderSystem::processSprite(MatchedEntity &entity)
	{
		const auto &position = entity.getComponent<PositionComponent>();
		auto &sprite = this->getSprite(entity);

		sprite.setPosition({position.pos_x, position.pos_y});
		return sprite;
	}

	sf::Sprite &RenderSystem::getSprite(MatchedEntity &entity)
	{
		const auto &path = entity.getComponent<SpriteComponent>().texturePath;
		if (!_sprites.contains(path)) {
			_textures.insert({path, sf::Texture()});
			auto &tex = _textures.at(path);
			tex.loadFromFile(path);
			_sprites.insert({path, sf::Sprite(tex)});
		}
		return _sprites.at(path);
	}

} /* Engine::Render */
