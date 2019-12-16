/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#include "network/network_system.hpp"

namespace Engine::Network
{
		NetworkContainer::~NetworkContainer()
		{
			if (_thread != nullptr) {
				_thread->join();
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
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::openAsServer(unsigned short port)
		{
			if (_connectionState != CLOSED) {
				throw std::runtime_error("Connection already opened");
			}
			_connectionState = SERVER;
			_container = Server(_ioCtx, port);
			_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
		}

		void NetworkContainer::closeConnection()
		{
			_connectionState = CLOSED;
			_thread->join();
			_thread = nullptr;
		}

		void NetworkContainer::scheduleNetwork()
		{
			std::cout << "INSIED THREAD" << std::endl;
			while (_connectionState != CLOSED) {
				std::cout << "run ioctx" << std::endl;
				_ioCtx.run();
				std::cout << "AFTER RUN" << std::endl;
				_ioCtx.restart();
			}
			std::cout << "END OF THREAD" << std::endl;
		}

} /* Engine::Network */
