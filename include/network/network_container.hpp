/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#ifndef NETWORK_CONTAINER_HPP_EGUMDX5V
#define NETWORK_CONTAINER_HPP_EGUMDX5V

#include <variant>
#include <thread>

#include <boost/asio.hpp>

#include "network/inetwork.hpp"
#include "network/serialize.hpp"
#include "engine/definitions.hpp"

namespace Engine {
	class World;
	class System;
}

namespace Engine::Network
{
	namespace Client { class UDPClient; }
	namespace Server { class UDPServer; }

	/**
	 * @brief network abstraction for UDP server/client
	 */
	class NetworkContainer
	{
	public:
		enum ConnectionState {CLOSED, SERVER, CLIENT};
		using Client = Engine::Network::Client::UDPClient;
		using Server = Engine::Network::Server::UDPServer;
		//Notice the use of raw pointer here because of std::variant not accepting
		//std::reference_wrapper
		using NetContainer = std::variant<std::monostate,
			  Client *, Server *>;

		NetworkContainer() = delete;
		~NetworkContainer();
		NetworkContainer(World &world, RessourceStorage &ressources) :
			_world(world), _ressources(ressources)
		{}

		bool isConnectionOpened() const;

		/** @brief Connect to a distant server
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

		ConnectionState getConnectionState() const { return _connectionState; }

	private:
		void scheduleNetwork();

		World &_world;
		RessourceStorage &_ressources;
		enum ConnectionState _connectionState = CLOSED;
		std::unique_ptr<IUDPNetwork> _socketRef = nullptr;
		NetContainer _container;
		std::unique_ptr<std::thread> _thread = nullptr;
		boost::asio::io_context _ioCtx;
	};
}

#endif /* end of include guard: NETWORK_CONTAINER_HPP_EGUMDX5V */
