/*
** EPITECH PROJECT, 2019
** query
** File description:
** Query entities from their components
*/

#include <unordered_map>
#include "engine/query.hpp"

namespace Engine
{
	bool QueryBuilder::aContainsAllOfB(std::unordered_set<int64_t> const &a, std::unordered_set<int64_t> const &b) const
	{
		return std::all_of(b.begin(), b.end(), [&](int64_t uuid) {
				return a.contains(uuid);
			});
	}

	QueryResult QueryBuilder::getIntersection()
	{
		QueryResult results;

		for (auto &match : _sortingList) {
			auto &entity = _entities[match.first];
			if (this->aContainsAllOfB(entity.boundComponents(), _componentsUUIDs)) {
				results.push_back(MatchedEntity(entity, _uuid, match.second));
			}
		}
		return results;
	}

} /* Engine */
