/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#include <variant>
#include "network/network_container.hpp"

namespace Engine::Network
{
		NetworkContainer::~NetworkContainer()
		{
			if (_connectionState != CLOSED) {
				this->closeConnection();
			}
		}

		bool NetworkContainer::isConnectionOpened() const
		{
			return _connectionState != CLOSED;
		}

		NetworkContainer::Server &NetworkContainer::getAsServer()
		{
			if (_connectionState != SERVER) {
				throw std::runtime_error("No connection opened as server");
			}
			return std::get<Server>(*_container);
		}

		NetworkContainer::Client &NetworkContainer::getAsClient()
		{
			if (_connectionState != CLIENT) {
				throw std::runtime_error("No connection opened as server");
			}
			return std::get<Client>(*_container);
		}

		void NetworkContainer::openAsClient(std::string &host, std::string port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = CLIENT;
			_container = std::make_unique<NetContainer>(Client(_world, _ioCtx, host, port));
			_socketRef = std::get<Server>(*_container);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::openAsServer(unsigned short port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = SERVER;
			_container = std::make_unique<NetContainer>(Server(_world, _ioCtx, port));
			_socketRef = std::get<Server>(*_container);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::closeConnection()
		{
			_connectionState = CLOSED;
			_ioCtx.stop();
			_thread->join();
			_socketRef = std::nullopt;
			_thread.reset(nullptr);
			_container.reset(nullptr);
		}

		void NetworkContainer::scheduleNetwork()
		{
			_socketRef->get().setupConnection();
			while (_connectionState != CLOSED) {
				_ioCtx.run();
				_ioCtx.restart();
			}
		}

} /* Engine::Network */
