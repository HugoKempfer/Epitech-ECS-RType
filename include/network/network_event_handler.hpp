/*
** EPITECH PROJECT, 2019
** network_event_handler
** File description:
** Distribute and consume network events
*/

#ifndef NETWORK_EVENT_HANDLER_HPP_U8OUQCHM
#define NETWORK_EVENT_HANDLER_HPP_U8OUQCHM

#include "engine/concepts_impl.hpp"
#include "engine/event.hpp"
#include "network/serialize.hpp"
#include "engine/world.hpp"

namespace Engine::Network
{
	template <typename UUID, typename E>
	class NetworkEventHandler : public ISubscribe
	{
	public:
		NetworkEventHandler() = delete;
		NetworkEventHandler(World &world) :
			_netwokEventWorld(world), _subscribedUUID(world.uuidCtx.get<E>())
		{
			world.eventsCtx.subscribe<NetworkEvent<UUID>>(*this);
		}

		~NetworkEventHandler()
		{
			_netwokEventWorld.eventsCtx.unSubscribe<NetworkEvent<UUID>>(*this);
		}

		virtual void handleNetwork(E const &) = 0;

	private:
		void handleSubscribtion(Storable const &event) final
		{
			auto const &netEvent = event.cast<NetworkEvent<UUID> const &>();

			if (netEvent.typeUUID != _subscribedUUID) {
				return;
			}
			this->handleNetwork(netEvent.ar.template decode<E const &>());
		}

		World &_netwokEventWorld;
		const int64_t _subscribedUUID;
	};
} /* Engine::Network */


#endif /* end of include guard: NETWORK_EVENT_HANDLER_HPP_U8OUQCHM */
