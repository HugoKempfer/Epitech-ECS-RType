/*
** EPITECH PROJECT, 2019
** events
** File description:
** Built-in events
*/

#ifndef EVENTS_HPP_8MZRWO0E
#define EVENTS_HPP_8MZRWO0E

#include <SFML/Window/Event.hpp>
#include "engine/event.hpp"

namespace Engine::Render
{
	using Keyboard = sf::Event::KeyEvent;

	struct SignalEvent : public Event<SignalEvent> {
		SignalEvent() = delete;
		SignalEvent(World &world) : Event<SignalEvent>(world.uuidCtx) {}
		//Construct from sfml event
		SignalEvent(World &world, sf::Event::EventType event) : Event<SignalEvent>(world.uuidCtx)
		{
			using sf::Event;

			switch (event) {
				case Event::Closed:
					signal = CLOSE;
					break;
				case Event::LostFocus:
					signal = LOST_FOCUS;
					break;
				case Event::GainedFocus:
					signal = GAINED_FOCUS;
					break;
				default:
					break;
			}
		}

		enum SignalType {
			CLOSE,
			LOST_FOCUS,
			GAINED_FOCUS
		};
		SignalType signal;
	};

	struct MouseEvent : public Event<MouseEvent> {
		MouseEvent() = delete;
		MouseEvent(World &world) : Event<MouseEvent>(world.uuidCtx) {}
		//Construct from sfml event
		MouseEvent(World &world, sf::Event const &event) : Event<MouseEvent>(world.uuidCtx)
		{
			using sf::Event;

			switch (event.type) {
				case Event::MouseButtonPressed:
					action = BUTTON_PRESSED;
					actionedButton = static_cast<Button>(event.mouseButton.button);
					break;
				case Event::MouseButtonReleased:
					action = BUTTON_RELEASED;
					actionedButton = static_cast<Button>(event.mouseButton.button);
					break;
				case Event::MouseMoved:
					action = MOVE;
					actionedButton = NONE;
					break;
				default:
					throw std::runtime_error("Unimplemented event");
			}
			x = event.mouseMove.x;
			y = event.mouseMove.y;
		}

		enum MouseAction {
			BUTTON_PRESSED,
			BUTTON_RELEASED,
			MOVE,
		};

		MouseAction action;
		int x;
		int y;
		enum Button {LEFT, RIGHT, MIDDLE, XBUTTON1, XBUTTON2, NONE} actionedButton;
	};

	class KeystrokeEvent : public Event<KeystrokeEvent>
	{
	public:
		KeystrokeEvent() = delete;
		KeystrokeEvent(World &world, sf::Event const &event) :
			Event<KeystrokeEvent>(world.uuidCtx)
		{
			using sf::Event;

			switch (event.type) {
				case Event::TextEntered:
					actionType = TEXT_ENTERED;
					break;
				case Event::KeyPressed:
					actionType = KEY_PRESSED;
					break;
				case Event::KeyReleased:
					actionType = KEY_RELEASED;
					break;
				default:
					throw std::runtime_error("Unimplemented key event");
			}
			key = event.key;
		}
		enum {KEY_PRESSED, KEY_RELEASED, TEXT_ENTERED} actionType;
		Keyboard key;
	};

} /* Engine::Render */

#endif /* end of include guard: EVENTS_HPP_8MZRWO0E */
