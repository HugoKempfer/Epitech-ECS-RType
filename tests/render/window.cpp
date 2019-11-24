#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/world.hpp"
#include "engine/state.hpp"
#include "engine/component.hpp"
#include "engine/entity.hpp"
#include "render/window.hpp"

using namespace Engine;

namespace TestWindow
{
	class DamnState : public State<DamnState> {
	public:
		DamnState() = delete;
		~DamnState() = default;
		DamnState(World &world) : State<DamnState>(world) {}

		void onUpdate() final {
			static int cycle = 0;

			if (cycle == 10000) {
				_world.states.pop();
			}
			++cycle;
		}
	};
} /* Test::Window */

Test(Render, openWindow)
{
	using namespace Engine;
	using namespace Engine::Render;
	using namespace TestWindow;

	World world;
	world.states.push<DamnState>(world);
	world.registerSystem<WindowSystem>(world, 300, 300);
	world.run();
}
