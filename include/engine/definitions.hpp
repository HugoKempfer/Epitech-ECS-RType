/*
** EPITECH PROJECT, 2019
** definitions
** File description:
** Engine complex types definitions
*/

#include <unordered_map>
#include <vector>
#include <memory>
#include "game_storage.hpp"
#include "concepts_impl.hpp"
#include "uuid.hpp"
#include "storable.hpp"
#include "state_machine.hpp"
#include "dispatcher.hpp"
#include "event_context.hpp"

#ifndef DEFINITIONS_HPP_ZR8GBK0B
#define DEFINITIONS_HPP_ZR8GBK0B

namespace Engine
{
	using ComponentStorage =
		std::unordered_map<int64_t, std::vector<std::unique_ptr<Storable>>>;

	using RessourceStorage =
		std::unordered_map<int64_t, std::unique_ptr<Storable>>;
} /* Engine */

#endif /* end of include guard: DEFINITIONS_HPP_ZR8GBK0B */
