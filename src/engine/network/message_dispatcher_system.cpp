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
	void MessageDispatcherSystem::dispatchMessage(Server::Client &client)
	{
		while (client.pollMsg()) {
			/* TODO: Dispatch message */
		}
	}
	void MessageDispatcherSystem::run() {
		if (!_world.network.isConnectionOpened()) {
			return;
		}
		auto clients = _world.network.getAsServer().getClients();
		for (auto &client = clients.first; client != clients.second; ++client) {
			this->dispatchMessage(client->second);
		}

	}
} /* Engine::Network */
