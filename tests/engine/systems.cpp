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

class TestSystem : public System {
public:
	TestSystem(World &world, int &count) :
		System(world, {}, {world.uuidCtx.get<TestState>()}),
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
} /* TestSystem */

Test(System, registerSystem)
{
	World world;
	int count;

	world.registerSystem(std::make_unique<SystemNs::TestSystem>(world, count));
}

Test(System, runSystem)
{
	World world;
	int count = 0;

	world.registerSystem(std::make_unique<SystemNs::TestSystem>(world, count));
	world.states.push(std::make_unique<SystemNs::TestState>(world));
	world.run();
	cr_assert_eq(count, 3);
}
