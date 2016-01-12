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

		template<class T>
		constexpr T Min(const T& a, const T& b) noexcept
		{
			return a < b ? a : b;
		}

		template<class T, class... Tr>
		constexpr T Min(const T& a, const T& b, const Tr&... rest) noexcept
		{
			return a < b ? Min(a, rest...) : Min(b, rest...);
		}

		template<class T>
		constexpr T Max(const T&a, const T& b) noexcept
		{
			return a > b ? a : b;
		}

		template<class T, class... Tr>
		constexpr T Max(const T& a, const T& b, const Tr&... rest) noexcept
		{
			return a > b ? Max(a, rest...) : Max(b, rest...);
		}
	}
}