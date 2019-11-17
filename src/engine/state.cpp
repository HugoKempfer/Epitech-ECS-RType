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

	/* template <typename Item> */
	/* int64_t State<Item>::getUUID() const */
	/* { */
	/* 	return UUID; */
	/* } */

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

	void StateMachine::push(std::unique_ptr<IActionableState> newState)
	{
		if (!_states.empty()) {
			_states.top()->onPause();
		}
		_states.push(std::move(newState));
		_states.top()->onStart();
	}

	void StateMachine::emplace(std::unique_ptr<IActionableState> newState)
	{
		if (!_states.empty()) {
			_states.top()->onStop();
		}
		_states.emplace(std::move(newState));
	}

	bool StateMachine::empty() const { return _states.empty(); }
	IActionableState &StateMachine::current() { return *_states.top(); }

} /* Engine */
