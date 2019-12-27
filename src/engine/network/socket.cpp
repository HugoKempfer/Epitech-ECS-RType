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
#include "network/network_events.hpp"

namespace Engine::Network::Server
{

	UDPServer::UDPServer(World &world, boost::asio::io_context &ioCtx, unsigned short port)
		: _socket(ioCtx, udp::endpoint(udp::v4(), port)), _world(world)
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
		_socket.async_receive_from(buffer(_rcvBuff), _newRemoteEndpoint,
				boost::bind(&UDPServer::acceptNewClient, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void UDPServer::acceptNewClient(boost::system::error_code const &err, size_t size)
	{
		std::cout << "Got a new connection" << std::endl;
		if (err) {
			std::cerr << err.error_code::message() << std::endl;
		}
		const auto id = _clientIdAI++;
		std::cout.write(_rcvBuff.data(), 20);
		auto &client = _clients.insert({id, Server::Client(id, _newRemoteEndpoint, _socket)})
			.first->second;
		_rcvBuff.fill(0);
		_world.eventsCtx.publish<ConnectionEvent>(_world, ConnectionEvent::CONNECTED, id);
		this->listenForClients();
	}

	void UDPServer::broadcastMsg(Message &msg)
	{
		for (auto &client : _clients) {
			client.second.doSendMsg(msg);
		}
	}

	void Client::listenForMsg()
	{
		_socket.async_receive_from(
				boost::asio::buffer(_rcvBuff),
				_endpoint,
				boost::bind(&Client::rcvMsgCallback,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}

	void Client::doSendMsg(Message msg)
	{
		auto buff = std::make_shared<std::vector<std::byte>>(msg.getMessageBuffer());

		_socket.async_send_to(boost::asio::buffer(*buff),
				_endpoint,
				boost::bind(
					&Client::sendMsgCallback,
					this,
					msg,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}

	std::optional<Message> Client::pollMsg()
	{
		if (!_incomingMsg.size()) {
			return {std::nullopt};
		}
		{
			std::lock_guard<std::mutex> msgProcess(_msgMutex);
			auto msg = std::make_optional<Message>(_incomingMsg.front());
			_incomingMsg.pop();
			return msg;
		}
	}

	void Client::sendMsgCallback(Message msg, const boost::system::error_code &err, size_t size)
	{
		/* TODO: Handle err */
		std::cout << "Message sent" << std::endl;
		if (err) {
			std::cerr << "ERR WHILE SENDING MSG" << std::endl;
		}
	}

	void Client::rcvMsgCallback(const boost::system::error_code &err, size_t size)
	{
		Message msg;
		MessageHeader *hdr = reinterpret_cast<MessageHeader *>(_rcvBuff.c_array());
		std::cout << "Received a message" << std::endl;
		std::cout << "Lenght => " << hdr->payloadSize << std::endl;
		if (sizeof(MessageHeader) + hdr->payloadSize != size) {
			std::cerr << "SIZE MISMATCH" << std::endl;
		}
		msg.header = *hdr;
		for (auto it = sizeof(MessageHeader); it < hdr->payloadSize; ++it) {
			msg.payload.push_back(static_cast<std::byte>(_rcvBuff.at(it)));
		}
		{
			std::lock_guard<std::mutex> msgLock(_msgMutex);
			_incomingMsg.push(msg);
		}
		this->listenForMsg();
	}

} /* Engine::Network::Server */

namespace Engine::Network::Client
{
	UDPClient::UDPClient(World &world, boost::asio::io_context &ioCtx, std::string host, std::string port)
		: _resolver(ioCtx), _serverEndpoint(*_resolver.resolve({udp::v4(), host, port})),
		_socket(ioCtx), _world(world)
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

	void UDPClient::sendMsgCallback(Message msg, const boost::system::error_code &err, size_t)
	{
		/* TODO: Handle server msg send */
		if (err) {
			std::cerr << "Error while sending a message" << std::endl;
		}
	}

} /* Engine::Network::Client */
