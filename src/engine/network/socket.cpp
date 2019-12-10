/*
** EPITECH PROJECT, 2019
** socket
** File description:
** Async UDP socket abstraction
*/

#include "network/socket.hpp"

namespace Engine::Network::Server
{

	UDPServer::UDPServer (boost::asio::io_context &ioCtx, unsigned short port)
		: _socket(ioCtx, udp::endpoint(udp::v4(), port))
	{
		this->listenForClients();
	}

	//async method
	void UDPServer::listenForClients()
	{
		using namespace boost::asio;

		_socket.async_receive_from(buffer(_buff), _newRemoteEndpoint,
				boost::bind(&UDPServer::acceptNewClient, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void UDPServer::acceptNewClient(boost::system::error_code const &err, size_t size)
	{
		_clients.push_back(_newRemoteEndpoint);
		this->listenForClients();
	}

	void Client::doSendMsg(Message msg)
	{
		_outgoingMsg.push(msg);
	}

} /* Engine::Network::Server */

namespace Engine::Network::Client
{
	UDPClient::UDPClient(boost::asio::io_context &ioCtx, unsigned short port)
		: _resolver(ioCtx), _serverEndpoint(*_resolver.resolve(udp::v4(), "ip", "damn")),
		_socket(ioCtx)
	{
	}

	void UDPClient::connectTo(std::string const &host)
	{
		if (_serverEndpoint) {
			throw std::runtime_error("A connection is already established");
		}
		_serverEndpoint = *_resolver.resolve(udp::v4(), host, "damn");
		_socket.open();
	}
} /* Engine::Network::Client */
