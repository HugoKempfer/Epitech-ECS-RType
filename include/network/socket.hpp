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

#include "network/inetwork.hpp"
#include "network/message.hpp"
#include "engine/definitions.hpp"
#include "network/serialize.hpp"
#include "engine/prelude.hpp"

using boost::asio::ip::udp;

namespace Engine { class World; }

namespace Engine::Network
{
	class MessageInbox
	{
	public:
		MessageInbox() = default;

		void addToInbox(Message &msg);
		std::optional<Message> checkInbox();

	private:
		std::mutex _msgMutex;
		std::queue<Message> _incomingMsg;
	};
} /* Engine::Network */

namespace Engine::Network::Server
{
	using Message = Engine::Network::Message;
	class UDPServer;

	/**
	 * @brief Client representation for UDPServer
	 */
	class Client : public MessageInbox
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

		const int64_t id;

	private:
		void listenForMsg();
		void rcvMsgCallback(const boost::system::error_code &, size_t);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);

		std::mutex _msgMutex;
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
		using ClientStorage = std::unordered_map<int64_t, Client>;
		UDPServer() = delete;
		UDPServer(World &world, boost::asio::io_context &ioCtx, unsigned short port,
				RessourceStorage &ressources);

		void listenForClients();
		void setupConnection() final;
		Client &getClient(int64_t id) { return _clients.at(id); }
		void broadcastMsg(Message &);

		std::pair<ClientStorage::iterator, ClientStorage::iterator> getClients() noexcept
		{
			return {_clients.begin(), _clients.end()};
		}

		template <typename UUID, typename T>
		void broadcastEvent(UUID event)
		{
			auto factoryUUID = _world.uuidCtx.get<SerializationFactory<UUID>>();

			try {
				auto &factory = _ressources.at(factoryUUID)->template
					cast<SerializationFactory<UUID>>();
				auto ar = factory.template serialize<T>(event);
				auto msg = ar.toMessage();
				this->broadcastMsg(msg);
			} catch(std::out_of_range &e) {
				throw std::runtime_error("UUID requested not handled");
			}
		}

	private:
		void acceptNewClient(boost::system::error_code const &err, size_t size);

		World &_world;
		RessourceStorage &_ressources;
		udp::endpoint _newRemoteEndpoint;
		int64_t _clientIdAI = 0;
		ClientStorage _clients;
		boost::array<char, USHRT_MAX> _rcvBuff;
		udp::socket _socket;
	};

} /* Engine::Network */

namespace Engine::Network::Client
{
	/**
	 * @brief UDP client for client-side connection
	 */
	class UDPClient : public IUDPNetwork, public MessageInbox
	{
	public:
		UDPClient() = delete;
		UDPClient(World &world, boost::asio::io_context &ioCtx, std::string host,
				std::string port, RessourceStorage &ressources);

		void setupConnection() final;

		template <typename UUID, typename T>
		void broadcastEvent(T event)
		{
			const int64_t factoryUUID = _world.uuidCtx.get<SerializationFactory<UUID>>();

			try {
				auto &factory = _ressources.at(factoryUUID)->template
					cast<SerializationFactory<UUID>>();
				auto ar = factory.template serialize<T>(event);
				auto msg = ar.toMessage();
				this->doSendMsg(msg);
			} catch(std::out_of_range &e) {
			}
		}

		/**
		 * @brief Try to get one server Message
		 *
		 * @return Option holding a potential Client Message
		 */
		std::optional<Message> pollMsg();

	private:
		void listenServerMsg();
		void doSendMsg(Message &);
		void rcvMsgCallback(const boost::system::error_code &, size_t);
		void sendMsgCallback(Message msg, const boost::system::error_code &, size_t);

		World &_world;
		RessourceStorage &_ressources;
		udp::resolver _resolver;
		udp::endpoint _serverEndpoint;
		udp::socket _socket;
		boost::array<char, USHRT_MAX> _rcvBuff;
	};

} /* Engine::Network::Client */

#endif /* end of include guard: SOCKET_HPP_TYJTNNQR */
