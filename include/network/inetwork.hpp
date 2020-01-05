/*
** EPITECH PROJECT, 2019
** inetwork
** File description:
** Network interface over UDP Sockets
*/

#ifndef INETWORK_HPP_OVA3RXEW
#define INETWORK_HPP_OVA3RXEW

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

#endif /* end of include guard: INETWORK_HPP_OVA3RXEW */
