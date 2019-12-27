#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "engine/system.hpp"
#include "engine/query.hpp"
#include "engine/state.hpp"

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

Test(Components, intersectionQuery)
{
	class Component1 : public Component<Component1>
	{
	public:
		Component1() = delete;
		Component1(World &world) : Component<Component1>(world) {}
	};
	class Component2 : public Component<Component2>
	{
	public:
		Component2() = delete;
		Component2(World &world) : Component<Component2>(world) {}
	};
	class Component3 : public Component<Component3>
	{
	public:
		Component3() = delete;
		Component3(World &world) : Component<Component3>(world) {}
	};

	class UselessState : public State<UselessState> {
	public:
		UselessState() = delete;
		UselessState(World &world) : State<UselessState>(world) {}
	};

	class DamnSystem : public System {
	public:
		DamnSystem() = delete;
		DamnSystem(World &world) : System(
				world,
				{
					{
					world.uuidCtx.get<Component2>(),
					world.uuidCtx.get<Component1>()
					}
				}, {})
		{}

		void run() final
		{
			auto damn = _world.entities.query(*this)
				.with<Component1>()
				.with<Component2>()
				.getIntersection();
			cr_assert_eq(2, damn.size());
			cr_assert_eq(2, damn[0].entity.id);
			cr_assert_eq(0, damn[1].entity.id);
			_world.states.pop();
		}
	};

	World world;
	world.entities.add().addComponent<Component1>(world).addComponent<Component2>(world);
	world.entities.add().addComponent<Component1>(world).addComponent<Component3>(world);
	world.entities.add().addComponent<Component1>(world).addComponent<Component3>(world).addComponent<Component2>(world);
	world.states.push<UselessState>(world);
	world.registerSystem<DamnSystem>(world);
	world.run();
}
