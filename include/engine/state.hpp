/*
** EPITECH PROJECT, 2019
** state
** File description:
** represent a game state
*/

#ifndef STATE_HPP_ZTLJ0BVE
#define STATE_HPP_ZTLJ0BVE

#include <iostream>
#include <unordered_set>
#include <memory>
#include <stack>
#include <vector>
#include <functional>
#include "storable.hpp"

using std::reference_wrapper;

namespace Engine
{
	class World;

	class IActionableState
	{
	public:
		IActionableState() = default;
		virtual ~IActionableState();

		virtual void onStart() = 0;
		virtual void onPause() = 0;
		virtual void onResume() = 0;
		virtual void onStop() = 0;
		virtual void onUpdate() = 0;
		virtual int64_t getUUID() const = 0;
		virtual const std::unordered_set<int64_t> &getRessourceAccessList() const = 0;
	};

	template <typename Item>
	class State : public Storable, public IActionableState
	{
	public:
		State() = delete;
		State(World &world);

		virtual ~State();

		int64_t getUUID() const final;
		const std::unordered_set<int64_t> &getRessourceAccessList() const final
		{return _ressourceAccess;}

	protected:
		std::unordered_set<int64_t> _ressourceAccess;
	};

	class StateMachine
	{
	public:
		StateMachine() = default;
		~StateMachine() = default;

		template <typename T> requires derived_from<T, State<T>>
		void push(std::unique_ptr<T> newState)
		{
			if (!_states.empty()) {
				_states.top()->onPause();
			}
			_states.push(std::move<newState>);
		}

		template <typename T> requires derived_from<T, State<T>>
		void emplace(T newState)
		{
			if (!_states.empty()) {
				_states.top()->onStop();
			}
			_states.emplace(std::move<newState>);
		}

		bool empty() const { return _states.empty(); }
		void pop();
		IActionableState &current() { return *_states.top(); }

	private:
		std::stack<std::unique_ptr<IActionableState>> _states;
	};

} /* Engine */

#endif /* end of include guard: STATE_HPP_ZTLJ0BVE */
