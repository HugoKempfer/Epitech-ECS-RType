/*
** EPITECH PROJECT, 2019
** message_dispatcher_system
** File description:
** System that dispatches incoming messages
*/

#ifndef MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR
#define MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR

#include "engine/prelude.hpp"

using Engine::System;

namespace Engine::Network
{
	class MessageDispatcherSystem : public System
	{
	public:
		MessageDispatcherSystem() = delete;
		MessageDispatcherSystem(World &world) :
			System(world, {}, {}) {}

		~MessageDispatcherSystem();

		void run() final;
	private:
		void dispatchMessage(Server::Client &);
	};
} /* Engine::Network */


#endif /* end of include guard: MESSAGE_DISPATCHER_SYSTEM_HPP_JLCHUQBR */
