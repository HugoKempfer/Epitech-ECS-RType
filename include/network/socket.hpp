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

	/**
	 * @brief Client representation for UDPServer
	 */
	class Client
	{
	public:
		Client (int64_t id, udp::endpoint endpoint, udp::socket &socket) :
			id(id), _endpoint(endpoint), _socket(socket) {}
		Client(Client const &old) :
			id(old.id), _endpoint(old._endpoint), _socket(old._socket) {}

		/**
		 * @brief Asynchronously send a message to the remote client
		 *
		 * @param msg Msg registered in the network factory
		 */
		void doSendMsg(Message msg);

		/**
		 * @brief Tru to get one client Message
		 *
		 * @return Monad holding a potentiel Client Message
		 */
		std::optional<Message> pollMsg();

		const int64_t id;

	private:
		void listenForMsg();
		void rcvMsgCallback(const boost::system::error_code &, size_t);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);

		std::mutex _msgMutex;
		std::queue<Message> _incomingMsg;
		udp::socket &_socket;
		udp::endpoint _endpoint;
		boost::array<char, USHRT_MAX> _rcvBuff;

		friend UDPServer;
	};

	/**
	 * @brief UDP server
	 */
	class UDPServer : public IUDPNetwork
	{
	public:
		UDPServer() = delete;
		UDPServer(World &world, boost::asio::io_context &ioCtx, unsigned short port);

		void listenForClients();
		void setupConnection() final;
		Client &getClient(int64_t id) { return _clients.at(id); }

	private:
		void acceptNewClient(boost::system::error_code const &err, size_t size);

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
	/**
	 * @brief UDP client for client-side connection
	 */
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
