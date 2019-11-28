/*
** EPITECH PROJECT, 2019
** bundle
** File description:
** Group of little logic unit
*/

#ifndef BUNDLE_HPP_KHVY9QWN
#define BUNDLE_HPP_KHVY9QWN

namespace Engine
{
	class World;
} /* Engine */

using Engine::World;

class Bundle
{
public:
	Bundle() = delete;
	Bundle(World &world) : _world(world) {}

	void apply()
	{
		this->registerRessources(_world);
		this->registerEntities(_world);
		this->registerSystems(_world);
	}

	virtual void registerRessources(World &world) {}
	virtual void registerSystems(World &world) {}
	virtual void registerEntities(World &world) {}
private:
	World &_world;
};

#endif /* end of include guard: BUNDLE_HPP_KHVY9QWN */
