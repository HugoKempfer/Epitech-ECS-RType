/*
** EPITECH PROJECT, 2d file descriptor019
** socket
** File description:
** Async UDP socket abstraction
*/

#include <array>
#include <memory>

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "network/socket.hpp"
#include "network/message.hpp"

namespace Engine::Network::Server
{

	UDPServer::UDPServer(boost::asio::io_context &ioCtx, unsigned short port)
		: _socket(ioCtx, udp::endpoint(udp::v4(), port))
	{}

	void UDPServer::setupConnection()
	{
		this->listenForClients();
	}

	//async method
	void UDPServer::listenForClients()
	{
		using namespace boost::asio;

		std::cout << "Listening for clients" << std::endl;
		std::cout << "The socket is => " << _socket.is_open() << std::endl;
		_socket.async_receive_from(buffer(_rcvBuff), _newRemoteEndpoint,
				boost::bind(&UDPServer::acceptNewClient, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void UDPServer::pollClientsMsg()
	{
		for (auto &client : _clients) {
			_socket.async_receive_from(boost::asio::buffer(_rcvBuff),
					client.second._endpoint,
					boost::bind(&UDPServer::rcvMsgCallback,
						this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		}
	}

	void UDPServer::acceptNewClient(boost::system::error_code const &err, size_t size)
	{
		std::cout << "Got a new connection" << std::endl;
		if (err) {
			std::cerr << err.error_code::message() << std::endl;
		}
		auto id = _clientIdAI++;
		std::cout.write(_rcvBuff.data(), 20);
		_clients.insert({id, Client(id, _newRemoteEndpoint, *this)});
		_rcvBuff.fill(0);
		this->listenForClients();
	}


	void UDPServer::sendMsgToClient(const Message &msg, Client &client)
	{
		auto buff = std::make_shared<std::vector<std::byte>>(msg.getMessageBuffer());

		_socket.async_send_to(boost::asio::buffer(*buff),
				client._endpoint,
				boost::bind(
					&UDPServer::sendMsgCallback,
					this,
					msg,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}

	void UDPServer::sendMsgCallback(Message msg, const boost::system::error_code &err, size_t size)
	{
		/* TODO: Handle err */
		std::cout << "Message sent" << std::endl;
		if (err) {
			std::cerr << "ERR WHILE SENDING MSG" << std::endl;
		}
	}

	void UDPServer::rcvMsgCallback(const boost::system::error_code &err, size_t size)
	{
		std::cout << "Received a message" << std::endl;
		/* TODO: Process received message */
	}

	void Client::dispatchMessages()
	{
		while (_outgoingMsg.size()) {
			auto &msg = _outgoingMsg.front();
			_server.sendMsgToClient(msg, *this);
			_outgoingMsg.pop();
		}
	}

	void Client::doSendMsg(Message msg)
	{
		_outgoingMsg.push(msg);
		this->dispatchMessages();
	}

} /* Engine::Network::Server */

namespace Engine::Network::Client
{
	UDPClient::UDPClient(boost::asio::io_context &ioCtx, std::string host, std::string port)
		: _resolver(ioCtx), _serverEndpoint(*_resolver.resolve({udp::v4(), host, port})),
		_socket(ioCtx)
	{
		_socket.open(udp::v4());
	}

	void UDPClient::setupConnection()
	{
		this->listenServerMsg();
	}

	void UDPClient::listenServerMsg()
	{
		using namespace boost::asio;

		_socket.async_receive_from(buffer(_rcvBuff), _serverEndpoint,
				boost::bind(&UDPClient::rcvMsgCallback, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void UDPClient::rcvMsgCallback(const boost::system::error_code &, size_t)
	{
		/* TODO: Handle server msg */
		this->listenServerMsg();
	}

	void UDPClient::sendMsgCallback(Message msg, const boost::system::error_code &, size_t)
	{
		/* TODO: Handle server msg send */
	}

} /* Engine::Network::Client */
