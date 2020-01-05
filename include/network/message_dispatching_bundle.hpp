/*
** EPITECH PROJECT, 2019
** message_dispatching_bundle
** File description:
** Automatic setup for message serialization and dispatching
*/

#ifndef MESSAGE_DISPATCHING_BUNDLE_HPP_QKV1GY6E
#define MESSAGE_DISPATCHING_BUNDLE_HPP_QKV1GY6E

#include <memory>
#include <functional>

#include "engine/prelude.hpp"
#include "engine/bundle.hpp"
#include "network/network_container.hpp"
#include "network/message_dispatcher_system.hpp"

namespace Engine::Network
{
	template <typename UUID>
	class MessageDispatchingBundle : Bundle
	{
	public:
		MessageDispatchingBundle() = delete;
		MessageDispatchingBundle(World &world,
				std::function<void(SerializationFactory<UUID> &)> init) : Bundle(world)
		{
			_factory = std::make_shared<SerializationFactory<UUID>>(world, init);
		}

		void registerRessources(World &world) final
		{
			world.registerRessource<SerializationFactoryRessource<UUID>>(world, _factory);
		}

		void registerSystems(World &world) final
		{
			world.registerSystem<MessageDispatcherSystem<UUID>>(world, _factory);
		}

	private:
		std::shared_ptr<SerializationFactory<UUID>> _factory;
	};

} /* Engine::Network */
#endif /* end of include guard: MESSAGE_DISPATCHING_BUNDLE_HPP_QKV1GY6E */
