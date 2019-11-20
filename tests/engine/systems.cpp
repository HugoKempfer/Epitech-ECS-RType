#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "engine/system.hpp"
#include "engine/state.hpp"

using namespace Engine;

namespace SystemNs
{
	class TestState : public State<TestState> {
	public:
		TestState(World &world): State<TestState>(world) {}
	};

	class TestComponent : public Component<TestComponent>
	{
	public:
		TestComponent(World &world, std::string &str):
			Component<TestComponent>(world), msg(str) {}

		const std::string &msg;
	};

	class TestSystem : public System {
	public:
		TestSystem(World &world, int &count) :
			System(world,
					{},
					{world.uuidCtx.get<TestState>()}),
			_count(count)
		{}
		~TestSystem() = default;

		void run() final {
			++_count;
			if (_count == 3) {
				_world.states.pop();
			}
		}
	private:
		int &_count;
	};

	class TestSystem2 : public System {
	public:
		TestSystem2(World &world) :
			System(world,
					{world.uuidCtx.get<TestComponent>()},
					{world.uuidCtx.get<TestState>()})
		{}

		~TestSystem2() = default;

		void run() final {
			auto components = this->getComponents<TestComponent>();

			cr_assert_eq(components[0].get().msg, std::string("damn daniel"));
			_world.states.pop();
		}
	};
} /* TestSystem */

Test(System, registerSystem)
{
	World world;
	int count;

	world.registerSystem<SystemNs::TestSystem>(world, count);
}

Test(System, runSystem)
{
	World world;
	int count = 0;

	world.registerSystem<SystemNs::TestSystem>(world, count);
	world.states.push<SystemNs::TestState>(world);
	world.run();
	cr_assert_eq(count, 3);
}

Test(System, getComponent)
{
	using namespace SystemNs;
	int count;
	std::string damn("damn daniel");

	World world;

	world.states.push<TestState>(world);
	world.entities.add().addComponent<TestComponent>(world, damn);
	world.registerSystem<TestSystem2>(world);
	world.run();
}
