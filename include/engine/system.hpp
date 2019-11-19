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
#include "world.hpp"

namespace Engine
{
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

		virtual ~System() = default;
		void registerComponentStorage(int64_t, std::vector<std::unique_ptr<Storable>> &);

		const std::unordered_set<int64_t> writeComponentAccess;
		const std::unordered_set<int64_t> executeOnState;
		const State getState() const { return _systemState; }
		virtual void run() = 0;

	protected:
		template <typename C> requires derived_from<C, Component<C>>
		std::vector<std::reference_wrapper<C>> getComponents()
		{
			auto components = std::vector<std::reference_wrapper<C>>();

			try {
				auto uuid = _world.uuidCtx.get<C>();
				std::vector<std::unique_ptr<Storable>> &ref = _component.at(uuid).get();
				for (auto &component : ref) {
					components.push_back({static_cast<C &>(*component)});
				}
			} catch(std::exception e) {
				throw e;
			}
			return components;
		}

		World &_world;
		State _systemState = INIT;

	private:
		std::unordered_map<int64_t, std::reference_wrapper<std::vector<std::unique_ptr<Storable>>>> _component;
	};

} /* Engine */

#endif /* end of include guard: SYSTEM_HPP_ZXPHWOR7 */
