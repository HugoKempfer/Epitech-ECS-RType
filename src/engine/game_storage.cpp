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
#include <functional>
#include <unordered_map>
#include "engine/game_storage.hpp"

using namespace Engine;
using std::mutex;

int &EntityStorage::add() {
	std::lock_guard<mutex> lock(_entityProcessing);

	_entities[_idAI] = 0;
	/* TODO: change 0 ofr actual entity class */
	return _entities.at(_idAI++);
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
