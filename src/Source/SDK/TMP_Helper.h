#pragma once

#include <type_traits>

namespace HE
{
	// Test if type T supports the operation Op
	// Example: 
	// template<typename T>
	// using try_size = decltype(std::declval<T>().size());
	// template<typename T, class Enable = std::enable_if_t<has_op<T, has_size>>>
	// auto foo(T t) { return t.size(); }
	template<class T, template<class> class Op, class = std::void_t<>>
	struct has_op : std::false_type {};

	template<class T, template<class> class Op>
	struct has_op<T, Op, std::void_t<Op<T>>> : std::true_type {};

	// TMP logic operators
	template<class Cond>
	struct not_ : std::conditional_t<Cond::value, std::false_type, std::true_type> {};

	template< class... Conds>
	struct and_ : std::true_type {};

	template< class Cond, class... Conds>
	struct and_<Cond, Conds...> : std::conditional_t<Cond::value, and_<Conds...>, std::false_type> {};

	static_assert(and_<std::is_integral<size_t>, std::is_arithmetic<size_t>>::value, "Test fail");

	template< class... Conds>
	struct or_ : std::false_type {};

	template< class Cond, class... Conds>
	struct or_<Cond, Conds...> : std::conditional_t<Cond::value, std::true_type, or_<Conds...>> {};

	template< class... Conds>
	struct equal_ : std::true_type {};

	template< class Cond1, class Cond2, class... Conds >
	struct equal_<Cond1, Cond2, Conds...> : std::conditional_t<Cond1::value == Cond2::value, equal_<Cond2, Conds...>, std::false_type> {};



	// StateSize
	// Gets the size of the state of the object
	// Basically, like sizeof but works on void and returns 0 for empty PODS
	template<class T>
	class StateSize : public std::integral_constant<size_t, std::is_empty<T>::value ? 0 : sizeof(T)> {};
	template<>
	class StateSize<void> : public std::integral_constant<size_t, 0> {};

	static_assert(StateSize<size_t>::value == sizeof(size_t), "StateSize test fail");
	static_assert(StateSize<and_<>>::value == 0, "StateSize test fail");
	static_assert(StateSize<void>::value == 0, "StateSize test fail");
}