/*
** EPITECH PROJECT, 2019
** system
** File description:
** Single responsability game logic unit
*/

#ifndef SYSTEM_HPP_ZXPHWOR7
#define SYSTEM_HPP_ZXPHWOR7

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "storable.hpp"
#include "component.hpp"
#include "concepts_impl.hpp"

namespace Engine
{
	class World;

	class System
	{
		enum State {
			INIT,
			WAITING,
			RUNNING,
			STOPPED,
		};

	public:
		System() = delete;
		System(World &, std::unordered_set<int64_t>,
				std::unordered_set<int64_t>);

		virtual ~System();
		void registerComponentStorage(int64_t, std::vector<Storable> &);

		const std::unordered_set<int64_t> writeComponentAccess;
		const std::unordered_set<int64_t> executeOnState;
		const State getState() const { return _systemState; }

	protected:
		template <typename C> requires derived_from<C, Component<C>>
		std::vector<C> &getComponents()
		{
			try {
				auto uuid = _world.uuidCtx.get<C>();
				return static_cast<std::vector<C>>(_component[uuid].get());
			} catch(std::exception e) {
				std::cerr << e.what() << std::endl;
			}
		}

		State _systemState = INIT;

	private:
		std::unordered_map<int64_t, std::reference_wrapper<std::vector<Storable>>> _component;
		World &_world;
	};
} /* Engine */

#endif /* end of include guard: SYSTEM_HPP_ZXPHWOR7 */
