/*
** EPITECH PROJECT, 2019
** state_machine
** File description:
** Organize and store states
*/

#ifndef STATE_MACHINE_HPP_MXORX68U
#define STATE_MACHINE_HPP_MXORX68U

#include <memory>
#include <stack>
#include "concepts_impl.hpp"

namespace Engine
{
	template <typename S>
	class State;
	class IActionableState;

	class StateMachine
	{
	public:
		StateMachine() = default;
		~StateMachine() = default;

		void push(std::unique_ptr<IActionableState> newState);
		/* { */
		/* 	if (!_states.empty()) { */
		/* 		_states.top()->onPause(); */
		/* 	} */
		/* 	_states.push(std::move(newState)); */
		/* } */

		void emplace(std::unique_ptr<IActionableState> newState);
		/* { */
		/* 	if (!_states.empty()) { */
		/* 		_states.top()->onStop(); */
		/* 	} */
		/* 	_states.emplace(std::move(newState)); */
		/* } */

		bool empty() const;
		void pop();
		IActionableState &current();

	private:
		std::stack<std::unique_ptr<IActionableState>> _states;
	};

} /* Engine */

#endif /* end of include guard: STATE_MACHINE_HPP_MXORX68U */
