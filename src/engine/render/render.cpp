#include <iostream>
#include "render/window.hpp"
#include "render/sprite_component.hpp"

void damn()
{
	std::cout << "DAMN" << std::endl;
}

namespace Engine::Render
{
	void RenderSystem::run()
	{
		/* auto sprites = this->getComponents<SpriteComponent>(); */
		auto &window = this->getRessource<WindowRessource>().window;

		window.clear(sf::Color::Black);
		/* for (auto sprite : sprites) { */
		/* 	window.draw(this->getSprite(sprite.get().spritePath)); */
		/* } */
		/* TODO: Render every sprite component */
	}

	sf::Sprite &RenderSystem::getSprite(const std::string &path)
	{
		if (!_sprites.contains(path)) {
			/* TODO: insert sprite */
		}
		return _sprites.at(path);
	}

} /* Engine::Render */
