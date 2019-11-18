#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/state.hpp"

using namespace Engine;

class TestState : public State<TestState>
{
public:
	TestState(World &world, int &count) : State<TestState>(world), _damn(count)
{}
	~TestState() = default;

	void onStart() override {
		++_damn;
	}
	void onStop() override {
		++_damn;
	}
	void onUpdate() override {
		_world.states.pop();
	}

private:
	int &_damn;
};


Test(World, instance)
{
	World world;
	world.run();
}

Test(World, registerState)
{
	World world;
	int count = 0;

	world.states.push(std::make_unique<TestState>(world, count));
	world.run();
	cr_assert_eq(count, 2);
}

Test(World, registerEntity)
{
	Engine::World world;

	world.entities.add();
	auto second = world.entities.add();
	cr_assert_eq(second.id, world.entities[1].id);
}

Test(World, deleteEntity)
{
	class TestState2 : public State<TestState2>
	{
	public:
		TestState2(World &world) : State<TestState2>(world) {}
		~TestState2() = default;

		void onStart() override {
			_world.entities.add();
			_world.entities.add();
			_world.entities.add();
		}
		void onUpdate() override {
			if (cycle == 0) {
				auto entity = _world.entities[1];
				_world.entities.doRemove(entity.id);
				++cycle;
			} else {
				cr_assert_eq(_world.entities.size(), 2);
				_world.states.pop();
			}
		}
	private:
		int cycle = 0;
	};

	Engine::World world;
	world.states.push(std::make_unique<TestState2>(world));
	world.run();
	cr_assert_eq(world.entities.size(), 0);
}
