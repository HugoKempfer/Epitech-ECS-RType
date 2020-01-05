/*
** EPITECH PROJECT, 2019
** main
** File description:
** RType game server
*/

#include <iostream>

#include "engine/prelude.hpp"
#include "network/message.hpp"
#include "network/socket.hpp"

class DamnState : public Engine::State<DamnState>
{
public:
	DamnState() = delete;
	DamnState(World &world) : State<DamnState>(world) {}
	~DamnState() = default;
	/*! \enum Damn
	 *
	 *  enum made for server connection
	 */
	enum Damn { DAMN, WOW };
	void onStart() final
	{
		_world.network.openAsServer(12343);
	}

	void onUpdate() final
	{
		using Message = Engine::Network::Message;
		using Type = Engine::Network::MessageType;
		if (count < 10000000) {
			++count;
			return;
		}
		Engine::Network::Message msg = {{Type::UNRELIABLE_MESSAGE, 0, 69}, {}};
		try {
			auto &client = _world.network.getAsServer().getClient(0);
			client.doSendMsg(msg);
			count = 0;
		} catch(std::out_of_range &) {
			count = 0;
		}
	}

private:
	int count = 0;
};

int main()
{
	World world;

	world.states.push<DamnState>(world);
	std::cout << "before run" << std::endl;
	world.run();
	return 0;
}
