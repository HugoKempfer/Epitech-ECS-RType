/*
** EPITECH PROJECT, 2019
** network_system
** File description:
** System's embeded UDP socket
*/

#ifndef NETWORK_SYSTEM_HPP_DY3USCMH
#define NETWORK_SYSTEM_HPP_DY3USCMH

#include <variant>

#include "engine/world.hpp"
#include "engine/system.hpp"

namespace Engine::Network {

	template <typename UUID>
	class NetworkSystem : public System
	{
	public:
		NetworkSystem() = delete;
		NetworkSystem(World &world) : System(world, {}, {}), _factory(world.uuidCtx) {}
		~NetworkSystem() = default;

		/* void publishOverNetwork(Args && ...args) */
		/* { */
		/* 	using Network::NetworkContainer; */
		/* 	auto event = std::make_unique<E>(std::forward<Args>(args)...); */

		/* 	switch (_network.getConnectionState()) { */
		/* 		case NetworkContainer::SERVER: */
		/* 			break; */
		/* 		case NetworkContainer::CLIENT: */
		/* 			auto &client = _network.getAsClient(); */
		/* 			break; */
		/* 		/1* case NetworkContainer::CLOSED: *1/ */
		/* 		/1* 	break; *1/ */
		/* 	} */
		/* } */

		void run() final
		{
		}
	private:
		SerializationFactory<UUID> _factory;
	};
} /* Engine::Network */

#endif /* end of include guard: NETWORK_SYSTEM_HPP_DY3USCMH */
