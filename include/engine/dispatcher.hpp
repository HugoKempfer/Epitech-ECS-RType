/*
** EPITECH PROJECT, 2019
** dispatcher
** File description:
** store systems and schedule their execution
*/

#ifndef DISPATCHER_HPP_VX376VTL
#define DISPATCHER_HPP_VX376VTL

/* #include "system.hpp" */

#include <vector>
#include <memory>

namespace Engine
{
	class System;
	class Dispatcher
	{
	public:
		Dispatcher() = default;
		~Dispatcher() = default;

		std::vector<std::unique_ptr<System>> _systems;
	};
} /* Engine */

#endif /* end of include guard: DISPATCHER_HPP_VX376VTL */
