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
	void MessageDispatcherSystem<UUID>::dispatchMessage(Server::Client &client)
	{
		while (auto message = client.pollMsg()) {
			Archive<UUID> ar(message);
		}
	}
} /* Engine::Network */
