/*
** EPITECH PROJECT, 2019
** game_storage
** File description:
** store and process game containers
*/

#ifndef GAME_STORAGE_HPP_COZMWYCF
#define GAME_STORAGE_HPP_COZMWYCF

#include <vector>
#include <mutex>
#include <queue>
#include <atomic>
#include <unordered_map>
#include "entity.hpp"

namespace Engine {
	class World;

	class EntityStorage
	{
	public:
		EntityStorage() = delete;
		EntityStorage(World &world);
		~EntityStorage() = default;

		Entity &add();
		void doRemove(int id);
		void removeAll() { _removeAll = true; }

		Entity &operator[](std::size_t index);
	private:
		void processRemoval();

		World &_world;
		std::atomic_bool _removeAll = false;
		int64_t _idAI = 0; // write only under mutex lock
		std::mutex _entityProcessing;
		std::queue<int64_t> _removeQueue;
		std::unordered_map<int64_t, Entity> _entities;

		friend class World; //Let World access the private method processRemoval
	};
}

#endif /* end of include guard: GAME_STORAGE_HPP_COZMWYCF */
