/*
** EPITECH PROJECT, 2019
** message_dispatcher_system
** File description:
** System that dispatches incoming messages
*/

#include "network/message_dispatcher_system.hpp"
#include "network/socket.hpp"

namespace Engine::Network
{
	template <typename UUID>
	void MessageDispatcherSystem<UUID>::dispatchMessage(MessageInbox &inbox)
	{
		while (auto message = inbox.checkInbox()) {
			Archive<UUID> ar(message);
		}
	}
} /* Engine::Network */
