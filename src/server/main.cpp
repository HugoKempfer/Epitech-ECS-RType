/*
** EPITECH PROJECT, 2019
** main
** File description:
** RType game server
*/

#include <iostream>

#include "engine/prelude.hpp"
#include "network/network_system.hpp"

class DamnState : public Engine::State<DamnState>
{
public:
	DamnState() = delete;
	DamnState(World &world) : State<DamnState>(world) {}
	~DamnState() = default;

	void onStart() final
	{
		_world.network.openAsServer(12343);
	}
};

int main()
{
	World world;

	world.states.push<DamnState>(world);
	std::cout << "before run" << std::endl;
	world.run();
	return 0;
}
