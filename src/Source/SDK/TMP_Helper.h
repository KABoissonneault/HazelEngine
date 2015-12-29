#pragma once

namespace HE
{
	template<class T, template<class> class Op, class = std::void_t<>>
	struct has_op : std::false_type {};

	template<class T, template<class> class Op>
	struct has_op<T, Op, std::void_t<Op<T>>> : std::true_type {};

	template< class... Conds>
	struct and_ : std::true_type {};

	template< class Cond, class... Conds>
	struct and_<Cond, Conds...> : std::conditional_t<Cond::value, and_<Conds...>, std::false_type> {};

	template< class... Conds>
	struct or_ : std::true_type {};

	template< class Cond, class... Conds>
	struct or_<Cond, Conds...> : std::conditional_t<Cond::value, std::true_type, or_<Conds...>> {};


}