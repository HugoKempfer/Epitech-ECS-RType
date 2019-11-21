/*
** EPITECH PROJECT, 2019
** event_context
** File description:
** container for event collecting and dispatching
*/

#ifndef EVENT_CONTEXT_HPP_G7YQUTWN
#define EVENT_CONTEXT_HPP_G7YQUTWN

#include <queue>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include "storable.hpp"
#include "concepts_impl.hpp"
#include "event.hpp"
#include "uuid.hpp"

namespace Engine
{
	class World;

	class EventCtx
	{
	public:
		EventCtx() = delete;
		EventCtx(World &world);
		~EventCtx() = default;

		template <typename E> requires derived_from<E, Event<E>>
		void subscribe(ISubscribe const &subscriber)
		{
			const auto uuid = _uuid.get<E>();

			if (!_listeners.contains(uuid)) {
				_listeners.insert({uuid,
						std::vector<std::reference_wrapper<ISubscribe>>()});
			}
			_listeners.at(uuid).push_back(subscriber);
		}

		template <typename E, typename ... Args> requires derived_from<E, Event<E>>
		void publish(Args && ...args)
		{
			_events.push(std::make_unique<E>(std::forward<Args>(args)...));
		}

	private:
		void dispatchEvents();

		World &_world;
		UUIDContext &_uuid;
		std::queue<std::unique_ptr<Storable>> _events;
		std::unordered_map<int64_t, std::vector<std::reference_wrapper<ISubscribe>>>
			_listeners;

		friend World;
	};

} /* Engine */

#endif /* end of include guard: EVENT_CONTEXT_HPP_G7YQUTWN */
