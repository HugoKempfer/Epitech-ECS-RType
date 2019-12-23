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
	/**
	 * @brief network abstraction for UDP server/client
	 */
	class NetworkContainer
	{
	public:
		using Client = Engine::Network::Client::UDPClient;
		using Server = Engine::Network::Server::UDPServer;
		using NetContainer = std::variant<Client, Server>;

		NetworkContainer() = delete;
		~NetworkContainer();
		NetworkContainer(World &world) : _world(world), _container(nullptr)
		{}

		bool isConnectionOpened() const;
		/**
		 * @brief Connect to a distant server
		 *
		 * @param host server ipv4
		 * @param port server port
		 */
		void openAsClient(std::string &host, std::string port);

		/**
		 * @brief Open a connection and listen for clients
		 *
		 * @param port port to bind the service
		 */
		void openAsServer(unsigned short port);

		/**
		 * @brief Close the active connection and reset the network
		 */
		void closeConnection();

		/**
		 * @brief Access the server instance
		 *
		 * @return Server instance reference
		 */
		Server &getAsServer();

		/**
		 * @brief Access the client instance
		 *
		 * @return Client instance reference
		 */
		Client &getAsClient();

	private:
		void scheduleNetwork();

		World &_world;
		enum {CLOSED, SERVER, CLIENT} _connectionState = CLOSED;
		std::optional<std::reference_wrapper<IUDPNetwork>> _socketRef = std::nullopt;
		std::unique_ptr<NetContainer> _container;
		std::unique_ptr<std::thread> _thread = nullptr;
		boost::asio::io_context _ioCtx;
	};
} /* Engine::Network */

namespace Engine::Network::Server
{
	/* TODO: Implement system for message dispatching */
} /* Engine::Network::Server */

#endif /* end of include guard: NETWORK_SYSTEM_HPP_DY3USCMH */