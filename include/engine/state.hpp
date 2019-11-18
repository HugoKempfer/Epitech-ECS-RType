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
#include "world.hpp"

using std::reference_wrapper;

namespace Engine
{
	class IActionableState
	{
	public:
		IActionableState() = default;
		virtual ~IActionableState() = default;

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
		State(World &world) : _world(world), Storable(world.uuidCtx, world.uuidCtx.get<Item>())
		{}

		virtual ~State() = default;

		int64_t getUUID() const final { return UUID; }
		const std::unordered_set<int64_t> &getRessourceAccessList() const final
		{return _ressourceAccess;}

		void onStart() override {}
		void onPause() override {}
		void onResume() override {}
		void onStop() override {}
		void onUpdate() override {}

	protected:
		std::unordered_set<int64_t> _ressourceAccess;
		World &_world;
	};

} /* Engine */

#endif /* end of include guard: STATE_HPP_ZTLJ0BVE */
