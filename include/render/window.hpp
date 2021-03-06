/*
** EPITECH PROJECT, 2019
** window
** File description:
** Open and manage window instance
*/

#ifndef WINDOW_HPP_SK6QEY7C
#define WINDOW_HPP_SK6QEY7C

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "engine/system.hpp"
#include "engine/world.hpp"
#include "engine/event.hpp"
#include "render/ressources.hpp"
#include "render/sprite_component.hpp"
#include "engine/built_in/component/position.hpp"
#include "engine/query.hpp"

namespace Engine::Render
{

	class WindowSystem : public System
	{
	public:
		WindowSystem() = delete;
		WindowSystem (World &world, uint32_t height = 800, uint32_t width = 800) :
			System(world,
					{},
					{world.uuidCtx.get<WindowRessource>()}),
			_height(height),
			_width(width)
		{}

		void onStart() override
		{
			auto &window = this->getRessource<WindowRessource>().window;

			window.create(sf::VideoMode(_width, _height), "damn");
			window.setFramerateLimit(60);
			window.setVerticalSyncEnabled(true);
		}

		~WindowSystem() = default;

		void run() override;

	private:
		void handleEvent(sf::Event &event);
		const int _height;
		const int _width;
	};

	struct ToRender {
		ToRender(PositionComponent &pos, SpriteComponent &sprite) :
			pos(pos), sprite(sprite)
		{}
		ToRender(ToRender const &other) : pos(other.pos), sprite(other.sprite) {}

		void operator=(const ToRender &other) {
			pos = other.pos;
			sprite = other.sprite;
		}

		PositionComponent &pos;
		SpriteComponent &sprite;
	};

	class RenderSystem : public System
	{
	public:
		RenderSystem() = delete;
		RenderSystem(World &world) :
			System(world,
					{world.uuidCtx.get<SpriteComponent>(),
					world.uuidCtx.get<PositionComponent>()
					},
					{world.uuidCtx.get<WindowRessource>()})
		{}
		~RenderSystem() = default;

		void run() override;

	private:
		sf::Sprite &getSprite(ToRender &);
		sf::Sprite &processSprite(ToRender &, sf::Sprite &);

		std::unordered_map<std::string, sf::Sprite> _sprites;
		std::unordered_map<std::string, sf::Texture> _textures;
	};
} /* Engine::Render */


#endif /* end of include guard: WINDOW_HPP_SK6QEY7C */
