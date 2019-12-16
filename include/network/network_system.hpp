/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#ifndef NETWORK_SYSTEM_HPP_DY3USCMH
#define NETWORK_SYSTEM_HPP_DY3USCMH

#include <variant>

#include "network/socket.hpp"

namespace Engine { class World; }

namespace Engine::Network
{
	class NetworkContainer
	{
	public:
		NetworkContainer() = delete;
		~NetworkContainer();
		NetworkContainer(World &world) : _world(world), _container(std::nullopt)
		{}

		bool isConnectionOpened() const;
		void openAsClient(std::string &host, unsigned short port);
		void openAsServer(unsigned short port);
		void closeConnection();

	private:
		void scheduleNetwork();

		using Client = Engine::Network::Client::UDPClient;
		using Server = Engine::Network::Server::UDPServer;

			World &_world;
			enum {CLOSED, SERVER, CLIENT} _connectionState = CLOSED;
			std::optional<std::variant<Client, Server>> _container;
			std::unique_ptr<std::thread> _thread = nullptr;
			boost::asio::io_context _ioCtx;
	};
} /* Engine::Network */

namespace Engine::Network::Server
{
	/* TODO: Implement system for message dispatching */
} /* Engine::Network::Server */

#endif /* end of include guard: NETWORK_SYSTEM_HPP_DY3USCMH */
