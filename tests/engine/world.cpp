#include <criterion/criterion.h>
#include "engine/world.hpp"

Test(World, instance)
{
	Engine::World world;
	world.run();
}
