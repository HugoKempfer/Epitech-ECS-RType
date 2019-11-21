/*
** EPITECH PROJECT, 2019
** event
** File description:
** Messages container for pub/sub
*/

#include "engine/world.hpp"
#include "engine/event.hpp"
#include "engine/event_context.hpp"

namespace Engine
{
	EventCtx::EventCtx(World &world) : _world(world), _uuid(world.uuidCtx)
	{}

	void EventCtx::dispatchEvents()
	{
		while (!_events.empty()) {
			auto &currentEvent = *_events.front().get();
			for (auto &subscriber : _listeners.at(currentEvent.UUID)) {
				subscriber.get().handleSubscribtion(currentEvent);
			}
			_events.pop();
			/* TODO: at except not handled here => risky situation */
		}
	}

} /* Engine */
