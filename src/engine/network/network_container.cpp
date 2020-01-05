/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#include <variant>
#include <memory>
#include <any>

#include "engine/prelude.hpp"
#include "engine/world.hpp"
#include "network/message_dispatching_bundle.hpp"
#include "network/network_container.hpp"
#include "network/message_dispatcher_system.hpp"
#include "network/socket.hpp"

namespace Engine::Network
{
	NetworkContainer::~NetworkContainer()
	{
		if (_connectionState != CLOSED) {
			this->closeConnection();
		}
	}

	void NetworkContainer::openAsClient(std::string &host, std::string port)
	{
		if (_connectionState != CLOSED) {
			throw std::runtime_error("Connection already opened");
		}
		_connectionState = CLIENT;
		auto client = std::make_unique<Client>(_world, _ioCtx, host, port, _ressources);
		_container = &*client;
		_socketRef = std::move(client);
		_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
	}

	void NetworkContainer::openAsServer(unsigned short port)
	{
		if (_connectionState != CLOSED) {
			throw std::runtime_error("Connection already opened");
		}
		_connectionState = SERVER;
		auto server = std::make_unique<Server>(_world, _ioCtx, port, _ressources);
		_container = &*server;
		_socketRef = std::move(server);
		_thread = std::make_unique<std::thread>(&NetworkContainer::scheduleNetwork, this);
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
		return *std::get<Server *>(_container);
	}

	NetworkContainer::Client &NetworkContainer::getAsClient()
	{
		if (_connectionState != CLIENT) {
			throw std::runtime_error("No connection opened as server");
		}
		return *std::get<Client *>(_container);
	}

	void NetworkContainer::closeConnection()
	{
		_connectionState = CLOSED;
		_ioCtx.stop();
		_thread->join();
		_socketRef.reset(nullptr);
		_thread.reset(nullptr);
		_container = NetContainer();
	}

	void NetworkContainer::scheduleNetwork()
	{
		_socketRef->setupConnection();
		while (_connectionState != CLOSED) {
			_ioCtx.run();
			_ioCtx.restart();
		}
	}

} /* Engine::Network */
