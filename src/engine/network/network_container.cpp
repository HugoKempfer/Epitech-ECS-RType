/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#include <variant>
#include "network/network_system.hpp"

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

		void NetworkContainer::openAsClient(std::string &host, unsigned short port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = CLIENT;
			_container = Client(_ioCtx, host, port);
			/* _socketRef = std::get<Server>(*_container); */
			/* TODO: Un-comment when UDPclient implements IUDPNetwork */
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::openAsServer(unsigned short port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = SERVER;
			_container = Server(_ioCtx, port);
			_socketRef = std::get<Server>(*_container);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::closeConnection()
		{
			_connectionState = CLOSED;
			_ioCtx.stop();
			_thread->join();
			_thread = nullptr;
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
