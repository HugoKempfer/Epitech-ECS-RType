#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "engine/system.hpp"
#include "engine/state.hpp"
#include "engine/ressource.hpp"
#include "engine/event.hpp"

using namespace Engine;

namespace EventTestNs
{
	class TestEvent : public Event<TestEvent> {
	public:
		TestEvent(World &world, std::string str) :
			msg(str),
			Event<TestEvent>(world.uuidCtx) {}

		std::string msg;
	};

	class TestState : public State<TestState> {
	public:
		TestState(World &world): State<TestState>(world) {}

		void onStart()
		{
			_world.eventsCtx.publish<TestEvent>(_world, "damn daniel");
		}
	};

	class TestSystem : public System, EventHandler<TestEvent> {
	public:
		TestSystem(World &world, std::string &test) :
			System(world,
					{},
					{},
					{world.uuidCtx.get<TestState>()}),
			EventHandler<TestEvent>(world),
			_test(test)
		{}
		~TestSystem() = default;

		void run() final {}

		void handle(TestEvent const &event) const final
		{
			_test = event.msg;
			_world.states.pop();
		}

	private:
		std::string &_test;
	};
} /* EventTestNs */

Test(Event, sendEvent)
{
	using namespace EventTestNs;

	World world;
	std::string test;

	world.registerSystem<TestSystem>(world, test)
		.states.push<TestState>(world);
	world.run();
	cr_assert_eq(test, std::string("damn daniel"));
}
