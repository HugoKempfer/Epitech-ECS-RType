/*
** EPITECH PROJECT, 2019
** game_storage
** File description:
** store and process game containers
*/

#include <iostream>
#include <mutex>
#include <queue>
#include <vector>
#include <unordered_map>
#include "engine/game_storage.hpp"

using std::mutex;

namespace Engine
{
	EntityStorage::EntityStorage(World &world)
		: _world(world)
	{}

	Entity &EntityStorage::add() {
		std::lock_guard<mutex> lock(_entityProcessing);
		const int64_t id = _idAI++;

		return _entities.insert({id, Entity(id, _world)}).first->second;
	}

	void EntityStorage::doRemove(int id)
	{
		std::lock_guard<mutex> lock(_entityProcessing);

		_removeQueue.push(id);
	}

	void EntityStorage::processRemoval()
	{
		std::lock_guard<mutex> lock(_entityProcessing);

		while (!_removeQueue.empty()) {
			if (!_removeAll) {
				_entities.erase(_removeQueue.front());
			}
			_removeQueue.pop();
		}
		if (_removeAll) {
			_entities.clear();
			_removeAll = false;
		}
	}

	const Entity &EntityStorage::operator[](std::size_t index) const
	{
		return _entities.at(index);
	}

} /* Engine */
