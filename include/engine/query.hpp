/*
** EPITECH PROJECT, 2019
** query
** File description:
** Query entities from their components
*/

#ifndef QUERY_HPP_EYFHNTLC
#define QUERY_HPP_EYFHNTLC

#include <vector>
#include "concepts_impl.hpp"
#include "engine/definitions.hpp"
#include "engine/system.hpp"
#include "component.hpp"

namespace Engine
{

	class MatchedEntity
	{
		using EntityComponents = std::unordered_map<int64_t, std::reference_wrapper<Storable>>;

	public:
		MatchedEntity(Entity const &entity, UUIDContext &uuidCtx, EntityComponents components) :
		entity(entity),
		_uuidCtx(uuidCtx),
		_components(components)
		{}

		/*MatchedEntity(MatchedEntity const &old) : entity(old.entity),
		_uuidCtx(old._uuidCtx),
		_components(old._components) {}

		MatchedEntity &operator=(const MatchedEntity &other) {
			entity = other.entity;
			_uuidCtx = other._uuidCtx;
			_components = other._components;
			return *this;
		}*/
		template <typename C> requires derived_from<C, Component<C>>
		C &getComponent()
		{
			Storable &component = _components.at(_uuidCtx.get<C>());

			return component.cast<C &>();
		}

		const Entity & entity; // is functionally const
	private:
		UUIDContext &_uuidCtx;
		EntityComponents _components;
	};
	using QueryResult = std::vector<MatchedEntity>;

	class QueryBuilder
	{
	public:
		QueryBuilder() = delete;
		QueryBuilder(UUIDContext &uuid, EntityStorage &entities, System &sys) :
			_entities(entities),
			_uuid(uuid),
			_sys(sys)
		{}
		~QueryBuilder() = default;

		template <typename C> requires derived_from<C, Component<C>>
		QueryBuilder &with()
		{
			const auto uuid = _uuid.get<C>();
			auto components = _sys.getComponents<C>();

			if (_componentsUUIDs.contains(uuid)) {
				return *this;
			}
			_componentsUUIDs.insert(uuid);
			for (auto &component : components) {
				auto entityId = component.get().getEntityId();
				if (!_sortingList.contains(entityId)) {
					_sortingList.insert({entityId, {}});
				}
				auto &entityComponents = _sortingList.at(entityId);
				entityComponents.insert({component.get().UUID, component});
			}
			return *this;
		}

		std::vector<MatchedEntity> getIntersection();

	private:
		bool aContainsAllOfB(std::unordered_set<int64_t> const &,
				std::unordered_set<int64_t> const &) const;

		std::unordered_set<int64_t> _componentsUUIDs;
		EntityStorage &_entities;
		UUIDContext &_uuid;
		System &_sys;
		std::unordered_map<int64_t, std::unordered_map<int64_t, std::reference_wrapper<Storable>>>  _sortingList;
	};

} /* Engine */

#endif /* end of include guard: QUERY_HPP_EYFHNTLC */
