/*
** EPITECH PROJECT, 2019
** event
** File description:
** Messages container for pub/sub
*/

#ifndef EVENT_HPP_CEL6QDJN
#define EVENT_HPP_CEL6QDJN

#include <queue>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include "storable.hpp"
#include "concepts_impl.hpp"
#include "uuid.hpp"
#include "event_context.hpp"
#include "world.hpp"

namespace Engine
{
	class ISubscribe
	{
	public:
		ISubscribe() = default;
		virtual ~ISubscribe() = default;

		virtual void handleSubscribtion(Storable const &) const = 0;
	};

	template <typename T>
	class Event : public Storable
	{
	public:
		Event(UUIDContext &uuidCtx) : Storable(uuidCtx, uuidCtx.get<T>()) {}
	};

	template <typename E> requires derived_from<E, Event<E>>
	class EventHandler : ISubscribe {
	public:
		EventHandler() = delete;
		EventHandler(World &world)
		{
			world.eventsCtx.subscribe<E>(*this);
		}
		~EventHandler() = default;

		virtual void handle(E const &) const = 0;

	private:
		void handleSubscribtion(Storable const &event) const final
		{
			this->handle(static_cast<E const &>(event));
		}
	};

} /* Engine */

#endif /* end of include guard: EVENT_HPP_CEL6QDJN */
