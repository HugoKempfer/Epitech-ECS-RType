/*
** EPITECH PROJECT, 2019
** concepts_impl
** File description:
** Re-implementation of std concepts
*/

#ifndef CONCEPTS_IMPL_HPP_UMAVAPWQ
#define CONCEPTS_IMPL_HPP_UMAVAPWQ

#include <iostream>
#include <type_traits>

template<class Derived, class Base>
concept derived_from =
	std::is_base_of_v<Base, Derived> &&
	std::is_convertible_v<const volatile Derived*, const volatile Base*>;

template<class T>
concept destructible = std::is_nothrow_destructible_v<T>;

template<class T, class... Args>
concept constructible_from = destructible<T> && std::is_constructible_v<T, Args...>;

template<class T>
concept default_constructible = constructible_from<T>;

template <typename S>
concept serializable =
	std::is_pod<S>::value &&
	std::is_default_constructible<S>::value &&
	std::is_literal_type<S>::value;

#endif /* end of include guard: CONCEPTS_IMPL_HPP_UMAVAPWQ */
