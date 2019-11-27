/*
** EPITECH PROJECT, 2019
** storable
** File description:
** Represent Storable object
*/

#ifndef STORABLE_HPP_NLEOBAHD
#define STORABLE_HPP_NLEOBAHD

#include "uuid.hpp"
#include "concepts_impl.hpp"

namespace Engine
{
	class Storable
	{
	public:
		Storable() = delete;
		Storable(UUIDContext &context, int64_t uuid) :
			_context(context), UUID(uuid) {}
		virtual ~Storable() = default;

		template <typename DEST>
		DEST cast()
		{
			if (_context.get<DEST>() != this->UUID) {
				throw std::runtime_error("Bad end type");
			}
			return static_cast<DEST>(*this);
		}

		const int64_t UUID;

	private:
		UUIDContext &_context;
	};

} /* Engine */

#endif /* end of include guard: STORABLE_HPP_NLEOBAHD */
