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

		template <typename T, typename ... Args> requires derived_from<T, State<T>>
		void push(Args && ...args)
		{
			std::unique_ptr<IActionableState> state =
				std::make_unique<T>(std::forward<Args>(args)...);

			this->processPush(state);
		}

		template <typename T, typename ... Args> requires derived_from<T, State<T>>
		void emplace(Args && ...args)
		{
			std::unique_ptr<IActionableState> state =
				std::make_unique<T>(std::forward<Args>(args)...);

			this->processEmplace(state);
		}

		bool empty() const;
		void pop();
		IActionableState &current();

	private:
		void processPush(std::unique_ptr<IActionableState> &);
		void processEmplace(std::unique_ptr<IActionableState> &);

		std::stack<std::unique_ptr<IActionableState>> _states;
	};

} /* Engine */

#endif /* end of include guard: STATE_MACHINE_HPP_MXORX68U */
