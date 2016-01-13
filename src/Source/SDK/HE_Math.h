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

		template<class T1, class T2, class T = std::common_type_t<T1, T2>>
		constexpr T Min(const T1& a, const T2& b) noexcept
		{
			return a < b ? a : b;
		}

		template<class T1, class T2, class... Tr, class T = std::common_type_t<T1, T2, Tr...>>
		constexpr T Min(const T1& a, const T2& b, const Tr&... rest) noexcept
		{
			return Min(a, Min(b, rest...));
		}

		template<class T1, class T2, class T = std::common_type_t<T1, T2>>
		constexpr T Max(const T1& a, const T2& b) noexcept
		{
			return a > b ? a : b;
		}

		template<class T1, class T2, class... Tr, class T = std::common_type_t<T1, T2, Tr...>>
		constexpr T Max(const T1& a, const T2& b, const Tr&... rest) noexcept
		{
			return Max(a, Max(b, rest...));
		}

	}
}