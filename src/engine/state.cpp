/*
** EPITECH PROJECT, 2019
** state
** File description:
** represent a game state
*/

#include <stack>
#include "engine/state.hpp"
#include "engine/world.hpp"

namespace Engine
{
	void StateMachine::pop()
	{
		if (!_states.empty()) {
			_states.top().get().onStop();
		}
		_states.pop();
		if (!_states.empty()) {
			_states.top().get().onResume();
		}
	}

} /* Engine */
