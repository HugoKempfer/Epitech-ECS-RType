/*
** EPITECH PROJECT, 2019
** state
** File description:
** represent a game state
*/

#include <stack>
#include "engine/storable.hpp"
#include "engine/world.hpp"
#include "engine/state.hpp"

namespace Engine
{
	template <typename Item>
	State<Item>::State(World &world) : Storable(world.uuidCtx, world.uuidCtx.get<Item>())
	{}

	template <typename Item>
	int64_t State<Item>::getUUID() const
	{
		return UUID;
	}

	void StateMachine::pop()
	{
		if (!_states.empty()) {
			_states.top()->onStop();
		}
		_states.pop();
		if (!_states.empty()) {
			_states.top()->onResume();
		}
	}

} /* Engine */
