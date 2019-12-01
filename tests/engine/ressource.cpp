#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "engine/system.hpp"
#include "engine/state.hpp"
#include "engine/ressource.hpp"

Test(System, getRessource)
{
	using namespace Engine;

	class DamnRessource : public Ressource<DamnRessource> {
	public:
		DamnRessource(World &world, std::string str)
			: Ressource(world), damn(str) {}

		std::string damn;
	};

	class TestState : public State<TestState> {
	public:
		TestState(World &world): State<TestState>(world) {}
	};

	class ResTestSys : public System {
	public:
		ResTestSys(World &world) :
			System(world,
					{},
					{world.uuidCtx.get<DamnRessource>()},
					{world.uuidCtx.get<TestState>()}
					) {}

		void run()
		{
			auto &res = this->getRessource<DamnRessource>();
			if (_cycle == 0) {
				cr_assert_eq(res.damn, std::string("damn daniel"));
				res.damn = "wow";
			} else {
				cr_assert_eq(res.damn, std::string("wow"));
				_world.states.pop();
			}
			++_cycle;
		}

	private:
		int _cycle = 0;
	};

	std::string damn("damn daniel");

	World world;
	world.registerRessource<DamnRessource>(world, "damn daniel")
		.registerSystem<ResTestSys>(world)
		.states.push<TestState>(world);
	world.run();
}
