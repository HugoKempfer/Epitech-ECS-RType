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
#include <unordered_map>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "network/message.hpp"

using boost::asio::ip::udp;

namespace Engine { class World; }

namespace Engine::Network
{
	class IUDPNetwork
	{
	public:
		IUDPNetwork() = default;
		virtual ~IUDPNetwork() = default;

		virtual void setupConnection() = 0;
	};

} /* Engine::Network */

namespace Engine::Network::Server
{
	using Message = Engine::Network::Message;
	class UDPServer;

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

	class UDPServer : public IUDPNetwork
	{
	public:
		UDPServer() = delete;
		UDPServer(World &world, boost::asio::io_context &ioCtx, unsigned short port);

		void sendMsgToClient(Message const &msg, Client &client);
		void pollClientsMsg();
		void listenForClients();
		void setupConnection() final;
		Client &getClient(int64_t id) { return _clients.at(id); }

	private:
		void acceptNewClient(boost::system::error_code const &err, size_t size);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);
		void rcvMsgCallback(const boost::system::error_code &, size_t);

		World &_world;
		udp::endpoint _newRemoteEndpoint;
		int64_t _clientIdAI = 0;
		std::unordered_map<int64_t, Client> _clients;
		boost::array<char, USHRT_MAX> _rcvBuff;
		udp::socket _socket;
	};

} /* Engine::Network */

namespace Engine::Network::Client
{
	class UDPClient : public IUDPNetwork
	{
	public:
		UDPClient() = delete;
		UDPClient(World &world, boost::asio::io_context &ioCtx, std::string host, std::string port);

		void setupConnection() final;

	private:
		void listenServerMsg();
		void rcvMsgCallback(const boost::system::error_code &, size_t);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);

		World &_world;
		udp::resolver _resolver;
		udp::endpoint _serverEndpoint;
		udp::socket _socket;
		boost::array<char, USHRT_MAX> _rcvBuff;
	};

} /* Engine::Network::Client */

#endif /* end of include guard: SOCKET_HPP_TYJTNNQR */
