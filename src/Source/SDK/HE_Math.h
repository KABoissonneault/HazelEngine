#pragma once

#include <type_traits>

#include "TMP_Helper.h"

namespace HE
{
	namespace Math
	{
		template<class T, class Enable = std::enable_if_t<std::is_integral<T>::value>>
		constexpr bool IsPow2(T a) noexcept
		{
			return a && !(a & (a - 1));
		}

		template<class T1, class T2>
		constexpr auto Min(const T1& a, const T2& b) noexcept
		{
			return a < b ? a : b;
		}

		template<class T1, class T2, class... Tr>
		constexpr auto Min(const T1& a, const T2& b, const Tr&... rest) noexcept
		{
			return Min(a, Min(b, rest...));
		}

		template<class T1, class T2>
		constexpr auto Max(const T1& a, const T2& b) noexcept
		{
			return a > b ? a : b;
		}

		template<class T1, class T2, class... Tr>
		constexpr auto Max(const T1& a, const T2& b, const Tr&... rest) noexcept
		{
			return Max(a, Max(b, rest...));
		}

		// Base should be non-zero and unsigned
		template<class T1, class T2, class Enable = std::enable_if_t<and_<std::is_integral<T1>, std::is_integral<T2>>::value>>
		constexpr auto RoundUpToMultipleOf(T1 s, T2 base) noexcept
		{
			return (s % base) ? s + base - (s % base) : s;
		}
	}
}