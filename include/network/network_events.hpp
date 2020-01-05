/*
** EPITECH PROJECT, 2019
** network_events
** File description:
** Events synchronized through the network
*/

#ifndef NETWORK_EVENTS_HPP_V87MD4NE
#define NETWORK_EVENTS_HPP_V87MD4NE

#include "engine/event.hpp"

namespace Engine::Network
{
	class ConnectionEvent: public Event<ConnectionEvent>
	{
	public:
		enum ActionType {CONNECTED, DISCONNECTED};

		ConnectionEvent() = delete;
		ConnectionEvent(World &world, ActionType type, int64_t id) :
			Event<ConnectionEvent>(world.uuidCtx),
			actionType(type), clientId(id)
		{}

		const ActionType actionType;
		const int64_t clientId;
	};

} /* Engine::Network */

#endif /* end of include guard: NETWORK_EVENTS_HPP_V87MD4NE */
