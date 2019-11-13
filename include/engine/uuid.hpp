/*
** EPITECH PROJECT, 2019
** uuid
** File description:
** Helper that generate UUID for class type
*/

#ifndef UUID_HPP_HTK69A2V
#define UUID_HPP_HTK69A2V

#include <atomic>

#define UNSET -1

namespace Engine
{
	class UUID
	{
	public:
		UUID() = default;
		~UUID() = default;

		template <typename Type>
		int64_t get()
		{
			static std::atomic_int64_t typeId = UNSET;

			if (typeId == UNSET) {
				typeId = _idAI++;
			}
			return typeId;
		}

	private:
		std::atomic_int64_t _idAI = 0;
	};
} /* Engine */

#endif /* end of include guard: UUID_HPP_HTK69A2V */
