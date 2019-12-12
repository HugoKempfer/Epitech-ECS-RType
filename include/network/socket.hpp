/*
** EPITECH PROJECT, 2019
** socket
** File description:
** Network socket abstraction
*/

#ifndef SOCKET_HPP_TYJTNNQR
#define SOCKET_HPP_TYJTNNQR

#include <list>
#include <functional>
#include <queue>
#include <climits>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "network/message.hpp"

using boost::asio::ip::udp;

namespace Engine::Network::Server
{
	using Message = Engine::Network::Message;
	class Client;

	class UDPServer
	{
	public:
		UDPServer() = delete;
		UDPServer(boost::asio::io_context &ioCtx, unsigned short port);

		void sendMsgToClient(Message const &msg, Client &client);
		void pollClientsMsg();

	private:

		void listenForClients();
		void acceptNewClient(boost::system::error_code const &err, size_t size);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);
		void rcvMsgCallback(const boost::system::error_code &, size_t);

		udp::endpoint _newRemoteEndpoint;
		std::list<udp::endpoint> _clients;
		boost::array<char, USHRT_MAX> _rcvBuff;
		udp::socket _socket;
	};

	class Client
	{
	public:
		Client (int64_t id, udp::endpoint endpoint, UDPServer &srv) :
			id(id), _endpoint(endpoint), _server(srv) {}

		void doSendMsg(Message msg);

		const int64_t id;
		std::queue<Message> _incomingMsg;

	private:
		void dispatchMessages();

		UDPServer &_server;
		udp::endpoint _endpoint;
		std::queue<Message> _outgoingMsg;

		friend UDPServer;
	};
} /* Engine::Network */

namespace Engine::Network::Client
{
	class UDPClient
	{
	public:
		UDPClient() = delete;
		UDPClient(boost::asio::io_context &ioCtx, unsigned short port);

		void connectTo(std::string const &);
	private:
		udp::resolver _resolver;
		std::optional<udp::endpoint> _serverEndpoint = std::nullopt;
		udp::socket _socket;
	};

} /* Engine::Network::Client */

#endif /* end of include guard: SOCKET_HPP_TYJTNNQR */
