/*
** EPITECH PROJECT, 2019
** message_dispatcher_system
** File description:
** System that dispatches incoming messages
*/

#ifndef MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR
#define MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR

#include <memory>
#include "engine/prelude.hpp"
#include "engine/ressource.hpp"
#include "network/network_container.hpp"
#include "network/socket.hpp"

using Engine::System;

namespace Engine::Network
{
	template <typename UUID>
	class SerializationFactoryRessource : public Ressource<SerializationFactoryRessource<UUID>>
	{
	public:
		SerializationFactoryRessource() = delete;
		SerializationFactoryRessource(World &world,
				std::shared_ptr<SerializationFactory<UUID>> fac)
			:
			Ressource<SerializationFactoryRessource<UUID>>(world), _factory(fac)
		{}

	private:
		std::shared_ptr<SerializationFactory<UUID>> _factory;
	};

	template <typename UUID>
	class MessageDispatcherSystem : public System
	{
	public:

		MessageDispatcherSystem() = delete;
		MessageDispatcherSystem(World &world) :
			System(world, {},
					{_world.uuidCtx.get<SerializationFactoryRessource<UUID>>()}) {}

		~MessageDispatcherSystem();

		void run() final
		{
			using Network::NetworkContainer;
			switch (_world.network.getConnectionState()) {
				case NetworkContainer::SERVER:
					{
						auto clients = _world.network.getAsServer().getClients();
						for (auto &client = clients.first; client != clients.second; ++client) {
							this->dispatchMessage(client->second);
						}
					}
					break;
				case NetworkContainer::CLIENT:
					{
						auto &client = _world.network.getAsClient();
						this->dispatchMessage(client);
					}
					break;
				case NetworkContainer::CLOSED:
					break;
			}
		}

	private:
		void dispatchMessage(MessageInbox &);
	};
} /* Engine::Network */


#endif /* end of include guard: MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR */
