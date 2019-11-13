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

namespace Engine {
	class EntityStorage
	{
	public:
		EntityStorage() = default;
		~EntityStorage() = default;

		int &add();
		void doRemove(int id);
		void removeAll() { _removeAll = true; }
		const int &operator[](std::size_t index) const { return _entities.at(index); }

	private:
		void processRemoval();

		std::atomic_bool _removeAll = false;
		int64_t _idAI = 0; // write only under mutex lock
		std::mutex _entityProcessing;
		std::queue<int64_t> _removeQueue;
		std::unordered_map<int64_t, int> _entities; /*! TODO: Change for real entity class
									 *  \todo Change for real entity class
									 */
		friend class World;
	};
}

#endif /* end of include guard: GAME_STORAGE_HPP_COZMWYCF */
