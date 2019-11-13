/*
** EPITECH PROJECT, 2019
** entity
** File description:
** game entity representation
*/

#ifndef ENTITY_HPP_K21ZN9ZT
#define ENTITY_HPP_K21ZN9ZT

#include <iostream>
#include <unordered_set>

class World;

namespace Engine {
	class Entity
	{
	public:
		Entity(int64_t id, World &world) : _id(id), _world(world) {};
		~Entity() = default;

	private:
		int64_t _id;
		World &_world;
		std::unordered_set<int> _boundComponentsType;
	};
}

#endif /* end of include guard: ENTITY_HPP_K21ZN9ZT */
