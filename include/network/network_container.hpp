/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#ifndef NETWORK_CONTAINER_HPP_EGUMDX5V
#define NETWORK_CONTAINER_HPP_EGUMDX5V

#include <variant>

#include "network/socket.hpp"
#include "network/serialize.hpp"

namespace Engine {
	class World;
	class System;
}

namespace Engine::Network
{
	/**
	 * @brief network abstraction for UDP server/client
	 */
	class NetworkContainer
	{
	public:
		enum ConnectionState {CLOSED, SERVER, CLIENT};
		using Client = Engine::Network::Client::UDPClient;
		using Server = Engine::Network::Server::UDPServer;
		using NetContainer = std::variant<Client, Server>;

		NetworkContainer() = delete;
		~NetworkContainer();
		NetworkContainer(World &world) : _world(world), _container(nullptr)
		{}

		bool isConnectionOpened() const;
		/** @brief Connect to a distant server
		 *
		 * @param host server ipv4
		 * @param port server port
		 */
		template <typename UUID>
		void openAsClient(std::string &host, std::string port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = CLIENT;
			_container = std::make_unique<NetContainer>(Client(_world, _ioCtx, host, port));
			_socketRef = std::get<Server>(*_container);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		/**
		 * @brief Open a connection and listen for clients
		 *
		 * @param port port to bind the service
		 */
		template <typename UUID>
		void openAsServer(unsigned short port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = SERVER;
			_container = std::make_unique<NetContainer>(Server(_world, _ioCtx, port));
			_socketRef = std::get<Server>(*_container);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

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
		enum ConnectionState _connectionState = CLOSED;
		std::optional<std::reference_wrapper<IUDPNetwork>> _socketRef = std::nullopt;
		std::unique_ptr<NetContainer> _container;
		std::unique_ptr<std::thread> _thread = nullptr;
		boost::asio::io_context _ioCtx;
	};
}

#endif /* end of include guard: NETWORK_CONTAINER_HPP_EGUMDX5V */
