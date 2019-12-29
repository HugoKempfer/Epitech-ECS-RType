/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#include <variant>
#include <memory>
#include "network/network_container.hpp"
#include "network/message_dispatcher_system.hpp"
#include "engine/prelude.hpp"
#include "engine/world.hpp"
#include "network/message_dispatching_bundle.hpp"

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
