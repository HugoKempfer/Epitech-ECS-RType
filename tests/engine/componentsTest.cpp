#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"

using namespace Engine;

class TestComponent : public Component<TestComponent>
{
public:
	TestComponent(World &world, std::string str) : Component<TestComponent>(world), damn(str) {}
	~TestComponent() = default;

	std::string damn;
};

Test(Component, create)
{
	World world;

	world.entities.add().addComponent<TestComponent>(world, "damn");
	auto &entity = world.entities[0];
	cr_assert(entity.boundComponents().contains(world.uuidCtx.get<TestComponent>()));
}

Test(Component, destroy)
{
	World world;

	world.entities.add().addComponent<TestComponent>(world, "damn");
	auto &entity = world.entities[0];
	cr_assert(entity.boundComponents().contains(world.uuidCtx.get<TestComponent>()));
	entity.removeComponent<TestComponent>();
	cr_assert_not(entity.boundComponents().contains(world.uuidCtx.get<TestComponent>()));
}
